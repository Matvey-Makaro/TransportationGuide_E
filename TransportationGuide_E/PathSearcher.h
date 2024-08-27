#pragma once

#include <memory>
#include <string>
#include <string_view>
#include <vector>
#include <optional>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include "graph.h"
#include "router.h"
#include "RoutingSettings.h"
#include "Path.h"

class Database;
class Route;
using RouteShp = std::shared_ptr<Route>;
using WeightType = double;

struct VertexData
{
  VertexData() :
    id(0),
    busName(),
    isFinal(false)
  {}

  VertexData(Graph::VertexId id, 
    std::string stopName, 
    std::optional<std::string> busName, 
    bool isFinal) :
    id(id),
    stopName(std::move(stopName)),
    busName(std::move(busName)),
    isFinal(isFinal)
  {}

  Graph::VertexId id;
  std::string stopName;
  std::optional<std::string> busName;
  bool isFinal;
  // bool isDummy?
};
using VertexDataShp = std::shared_ptr<VertexData>;


class PathSearcher
{
  using RouteGraph = Graph::DirectedWeightedGraph<WeightType>;
  using RouteGraphUnp = std::unique_ptr<RouteGraph>;
  using RouteEdge = Graph::Edge<WeightType>;
  using GraphRouter = Graph::Router<WeightType>;
  using GraphRouterUnp = std::unique_ptr<GraphRouter>;

public:
  PathSearcher();
  std::optional<Path> FindPath(const std::string& fromStopName, const std::string& toStopName);

  void Initialize(const Database& db, const RoutingSettings& settings);

private:
  void BuildGraph();
  void InitializeRouter();

  size_t CalculateVertexNum(const std::vector<RouteShp>& routes, size_t stopsNum) const;
  void BuildSubgraphForRoute(const Route& route);
  void BuildSubgraphForCommonRoute(const Route& route);
  void BuildSubgraphForCircleRoute(const Route& route);

  template<typename It>
  void BuildSubgraphForDirectRoute(const std::string& routeName, Range<It>& stopNames);

  // ребра-пересадки
  void BuildTransferEdges();

  void BuildDummyStartStopVertices();

  VertexDataShp CreateVertex(
    std::string stopName,
    std::optional<std::string> busName = std::nullopt ,
    bool isFinal = false);

  VertexDataShp CreateDummyVertex(
    std::string stopName,
    std::optional<std::string> busName = std::nullopt,
    bool isFinal = false);

  RouteEdge CreateEdge(const VertexData& from, const VertexData& to, WeightType weight);
  RouteEdge CreateEdge(Graph::VertexId fromId, Graph::VertexId toId, WeightType weight);

  double CalculateTimeBetweenStops(std::string_view from, std::string_view to) const;
  Graph::VertexId GetNextVertexId() const;

  std::optional<Graph::VertexId> GetStartDummyVertex(const std::string& stopName);
  std::optional<Graph::VertexId> GetFinishDummyVertex(const std::string& stopName);

  bool IsWaitEdge(const VertexData& from, const VertexData& to) const;

private:
  static const WeightType ZeroWeight;

  const Database* _db;
  RoutingSettings _routeSettings;
  RouteGraphUnp _graph;
  GraphRouterUnp _router;
  std::vector<VertexDataShp> _idToVertex;
  mutable Graph::VertexId _nextVertexId;
  std::map<std::string, std::unordered_set<Graph::VertexId>> _stopNameToVertices;

  struct StartFinishPair
  {
    Graph::VertexId start;
    Graph::VertexId finish;
  };
  std::unordered_map<std::string, StartFinishPair> _stopNameToDummyStartStopVertexId;
};
using PathSearcherShp = std::shared_ptr<PathSearcher>;
using PathSearcherWkp = std::weak_ptr<PathSearcher>;


template<typename It>
void PathSearcher::BuildSubgraphForDirectRoute(const std::string& routeName, Range<It>& stopNames)
{
  if (stopNames.begin() == stopNames.end())
    return;

  auto firstStopVertex = CreateVertex(*stopNames.begin(), routeName, true);
  VertexData* fromVertex = firstStopVertex.get();
  for (auto it = std::next(stopNames.begin()); it != stopNames.end(); it++)
  {
    const auto& stopName = *it;
    auto toVertex = CreateVertex(stopName, routeName, false);
    auto edge = CreateEdge(*fromVertex,
      *toVertex,
      CalculateTimeBetweenStops(fromVertex->stopName, toVertex->stopName));
    _graph->AddEdge(edge);
    fromVertex = toVertex.get();
  }
  fromVertex->isFinal = true;
}
