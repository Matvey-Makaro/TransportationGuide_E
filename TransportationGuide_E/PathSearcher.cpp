#include <optional>
#include <cassert>
#include "Database.h"
#include "Utiils.h"
#include "PathSearcher.h"

namespace
{
  class GraphRouteRAII
  {
  public:
    GraphRouteRAII(std::optional<typename Graph::Router<WeightType>::RouteInfo> routeInfo,
      Graph::Router<WeightType>* router) :
      _routeInfo(std::move(routeInfo)),
      _router(router)
    {}
    ~GraphRouteRAII()
    {
      if (_router == nullptr)
        return;
      if (!_routeInfo.has_value())
        return;
      _router->ReleaseRoute(_routeInfo->id);
    }

    const std::optional<typename Graph::Router<WeightType>::RouteInfo>& GetRouteInfo() const
    {
      return _routeInfo;
    }
    
  private:
    std::optional<typename Graph::Router<WeightType>::RouteInfo> _routeInfo;
    Graph::Router<WeightType>* _router;
  };
}

const WeightType PathSearcher::ZeroWeight = 0.;

PathSearcher::PathSearcher() :
  _db(nullptr),
  _routeSettings(),
  _graph(),
  _router(),
  _idToVertex(),
  _nextVertexId(0)
{}

std::optional<Path> PathSearcher::FindPath(const std::string& fromStopName, const std::string& toStopName)
{
  auto fromId = GetStartDummyVertex(fromStopName);
  auto toId = GetFinishDummyVertex(toStopName);
  if (!fromId || !toId)
    return std::nullopt;

  // Route завернуть в RAII
  GraphRouteRAII graphRouteRAII(_router->BuildRoute(*fromId, *toId), _router.get());
  const auto& routeInfo = graphRouteRAII.GetRouteInfo();
  if (!routeInfo.has_value())
    return std::nullopt;

  assert(routeInfo->edge_count >= 2);
  size_t startIdx = 1; // skip start dummy vertex
  size_t finishIdx = routeInfo->edge_count - 1; // skip finish dummy vertex
  double totalWeight = routeInfo->weight;

  std::vector<IPathElementShp> pathElements;
  if (startIdx < finishIdx)
  {
    auto edgeId = _router->GetRouteEdge(routeInfo->id, startIdx);
    auto edge = _graph->GetEdge(edgeId);
    auto fromVertexData = _idToVertex[edge.from];
    auto waitElement = std::make_shared<WaitPathElement>(fromVertexData->stopName, _routeSettings.BusWaitTime);
    pathElements.push_back(std::move(waitElement));
    totalWeight += _routeSettings.BusWaitTime;
  }

  for (size_t i = startIdx; i < finishIdx; i++)
  {
    auto edgeId = _router->GetRouteEdge(routeInfo->id, i);
    auto edge = _graph->GetEdge(edgeId);
    auto fromVertexData = _idToVertex[edge.from];
    auto toVertexData = _idToVertex[edge.to];
    IPathElementShp pathElement;
    if (IsWaitEdge(*fromVertexData, *toVertexData))
    {
      pathElement = std::make_shared<WaitPathElement>(toVertexData->stopName, _routeSettings.BusWaitTime);
    }
    else
    {
      assert(toVertexData->busName.has_value());
      pathElement = std::make_shared<BusPathElement>(*toVertexData->busName,
        fromVertexData->stopName,
        toVertexData->stopName,
        edge.weight);
    }
    pathElements.push_back(std::move(pathElement));
  }


  return Path(totalWeight, std::move(pathElements));
}

void PathSearcher::Initialize(const Database& db, const RoutingSettings& settings)
{
  _db = &db;
  _routeSettings = settings;
  BuildGraph();
  InitializeRouter();
}

void PathSearcher::BuildGraph()
{
  auto routes = _db->GetAllRoutes();
  auto totalStopsNum = _db->GetNumOfStops();
  auto vertexNum = CalculateVertexNum(routes, totalStopsNum);
  _graph = std::make_unique<RouteGraph>(vertexNum);
  _idToVertex.resize(vertexNum);

  for (const auto& r : routes)
  {
    BuildSubgraphForRoute(*r);
  }
  BuildTransferEdges();
  BuildDummyStartStopVertices();
}

void PathSearcher::InitializeRouter()
{
  assert(_graph);
  _router = std::make_unique<GraphRouter>(*_graph);
}

size_t PathSearcher::CalculateVertexNum(const std::vector<RouteShp>& routes, size_t stopsNum) const
{
  size_t totalVertexNum = 0;
  for (const auto& r : routes)
  {
    auto numOfStopsInFullRoute = r->GetNumOfStopsInFullRoute();
    if (r->GetType() == Route::Common)
    {
      totalVertexNum += numOfStopsInFullRoute + 1;
    }
    else
    {
      totalVertexNum += (numOfStopsInFullRoute - 1) * 2;
    }
  }
  // dummy vertex
  totalVertexNum += stopsNum * 2;
  return totalVertexNum;
}

void PathSearcher::BuildSubgraphForRoute(const Route& route)
{
  if (route.GetType() == Route::Common)
  {
    BuildSubgraphForCommonRoute(route);
  }
  else
  {
    BuildSubgraphForCircleRoute(route);
  }
}

void PathSearcher::BuildSubgraphForCommonRoute(const Route& route)
{
  const auto& stopNames = route.GetStopNames();
  Range directStopNames(stopNames.cbegin(), stopNames.cend());
  BuildSubgraphForDirectRoute(route.GetName(), directStopNames);
  Range reverseStopNames(stopNames.crbegin(), stopNames.crend());
  BuildSubgraphForDirectRoute(route.GetName(), reverseStopNames);
}

void PathSearcher::BuildSubgraphForCircleRoute(const Route& route)
{
  auto stopNames = route.GetFullRoute();
  auto firstStopVertex = CreateVertex(stopNames.front(), route.GetName(), true);
  VertexData* fromVertex = firstStopVertex.get();
  for (auto it = std::next(stopNames.cbegin()); it != stopNames.cend(); it++)
  {
    const auto& stopName = *it;
    auto toVertex = CreateVertex(stopName, route.GetName(), false);
    auto edge = CreateEdge(*fromVertex,
      *toVertex,
      CalculateTimeBetweenStops(fromVertex->stopName, toVertex->stopName));
    _graph->AddEdge(edge);
    fromVertex = toVertex.get();
  }
  fromVertex->isFinal = true;
  // Пересадка на первой конечке
  _graph->AddEdge(CreateEdge(*fromVertex, *firstStopVertex, _routeSettings.BusWaitTime));
}

void PathSearcher::BuildTransferEdges()
{
  // TODO: Сделать читаемым
  for (const auto& [stopName, verticesIds] : _stopNameToVertices)
  {
    if (verticesIds.size() < 2)
      continue;

    auto prevEndIt = std::prev(verticesIds.cend());
    for (auto i = verticesIds.cbegin(); i != prevEndIt; i++)
    {
      for (auto j = std::next(i); j != verticesIds.cend(); j++)
      {
        _graph->AddEdge(CreateEdge(*i, *j, _routeSettings.BusWaitTime));
        _graph->AddEdge(CreateEdge(*j, *i, _routeSettings.BusWaitTime));
      }
    }
  }
}

void PathSearcher::BuildDummyStartStopVertices()
{
  for (const auto& [stopName, verticesIds] : _stopNameToVertices)
  {
    auto dummyStart = CreateDummyVertex(stopName);
    auto dummyFinish = CreateDummyVertex(stopName);
    _stopNameToDummyStartStopVertexId[stopName] = StartFinishPair{ dummyStart->id, dummyFinish->id };

    for (const auto id : verticesIds)
    {
      _graph->AddEdge(CreateEdge(dummyStart->id, id, ZeroWeight));
      _graph->AddEdge(CreateEdge(id, dummyFinish->id, ZeroWeight));
    }
  }
}

VertexDataShp PathSearcher::CreateVertex(
  std::string stopName, 
  std::optional<std::string> busName, 
  bool isFinal)
{
  auto v = CreateDummyVertex(std::move(stopName), std::move(busName), isFinal);
  _stopNameToVertices[v->stopName].insert(v->id);
  return v;
}

VertexDataShp PathSearcher::CreateDummyVertex(
  std::string stopName, 
  std::optional<std::string> busName, 
  bool isFinal)
{
  auto v = std::make_shared<VertexData>();
  v->id = GetNextVertexId();
  v->stopName = std::move(stopName);
  v->busName = std::move(busName),
    v->isFinal = isFinal;
  _idToVertex[v->id] = v;
  return v;
}

PathSearcher::RouteEdge PathSearcher::CreateEdge(const VertexData& from, const VertexData& to, WeightType weight)
{
  return CreateEdge(from.id, to.id, weight);
}

PathSearcher::RouteEdge PathSearcher::CreateEdge(Graph::VertexId fromId, Graph::VertexId toId, WeightType weight)
{
  RouteEdge edge;
  edge.from = fromId;
  edge.to = toId;
  edge.weight = weight;
  return edge;
}

double PathSearcher::CalculateTimeBetweenStops(std::string_view from, std::string_view to) const
{
  auto roadLengthMeters = _db->GetRoadLength(from, to);
  return roadLengthMeters / KmHToMMin(_routeSettings.BusVelocityKmH);
}

Graph::VertexId PathSearcher::GetNextVertexId() const
{
  return _nextVertexId++;
}

std::optional<Graph::VertexId> PathSearcher::GetStartDummyVertex(const std::string& stopName)
{
  auto it = _stopNameToDummyStartStopVertexId.find(stopName);
  if (it == _stopNameToDummyStartStopVertexId.end())
    return std::nullopt;
  return it->second.start;
}

std::optional<Graph::VertexId> PathSearcher::GetFinishDummyVertex(const std::string& stopName)
{
  auto it = _stopNameToDummyStartStopVertexId.find(stopName);
  if (it == _stopNameToDummyStartStopVertexId.end())
    return std::nullopt;
  return it->second.finish;
}

bool PathSearcher::IsWaitEdge(const VertexData& from, const VertexData& to) const
{
  return from.stopName == to.stopName;
}



