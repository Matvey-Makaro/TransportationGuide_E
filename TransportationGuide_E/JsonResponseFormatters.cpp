#include <string>
#include <set>
#include <cassert>
#include "IResponse.h"
#include "OutputBusResponse.h"
#include "OutputStopResponse.h"
#include "InputBusResponse.h"
#include "InputStopResponse.h"
#include "FindRouteResponse.h"
#include "Path.h"
#include "Route.h"
#include "Stop.h"
#include "JsonResponseFormatters.h"

using namespace Json;
using namespace std;

RequestType Json::OutputBusResponseFormatter::GetType()
{
  return RequestType::OutputBus;
}

Node Json::OutputBusResponseFormatter::Format(const IResponse* response)
{
  ClearPreviousState();
  auto r = dynamic_cast<const OutputBusResponse*>(response);
  if (r == nullptr)
    return {};

  if (r->GetRoute() == nullptr)
  {
    FormatIfRouteNotFound(r);
  }
  else
  {
    DefaultFormat(r);
  }
  return Node(_responseNode);
}

void Json::OutputBusResponseFormatter::FormatIfRouteNotFound(const OutputBusResponse* r)
{
  FormatCommonPart(r);
  _responseNode["error_message"] = "not found"s;
}

void Json::OutputBusResponseFormatter::DefaultFormat(const OutputBusResponse* r)
{
  FormatCommonPart(r);

  _responseNode["stop_count"] = r->GetStopsOnRouteNum();
  _responseNode["unique_stop_count"] = r->GetUniqueStopsNum();
  _responseNode["route_length"] = r->GetRoadRouteLength();
  _responseNode["curvature"] = r->GetCurvature();
}

void Json::OutputBusResponseFormatter::FormatCommonPart(const OutputBusResponse* r)
{
  _responseNode["request_id"] = r->GetId();
}

void Json::OutputBusResponseFormatter::ClearPreviousState()
{
  _responseNode.clear();
}


RequestType Json::OutputStopResponseFormatter::GetType()
{
  return RequestType::OutputStop;
}

Node Json::OutputStopResponseFormatter::Format(const IResponse* response)
{
  ClearPreviousState();
  auto r = dynamic_cast<const OutputStopResponse*>(response);
  if (r == nullptr)
    return {};

  if (!r->IsStopExist())
  {
    FormatStopNotFound(r);
  }
  else
  {
    SuccessFormat(r);
  }
  return Node(_responseNode);
}

void Json::OutputStopResponseFormatter::FormatStopNotFound(const OutputStopResponse* r)
{
  FormatCommonPart(r);
  _responseNode["error_message"] = "not found"s;
}

void Json::OutputStopResponseFormatter::SuccessFormat(const OutputStopResponse* r)
{
  FormatCommonPart(r);
  _responseNode["buses"] = CreateNodeForRoutes(r->GetRoutes());
}

void Json::OutputStopResponseFormatter::FormatCommonPart(const OutputStopResponse* r)
{
  _responseNode["request_id"] = r->GetId();
}

Node Json::OutputStopResponseFormatter::CreateNodeForRoutes(const std::vector<RouteShp>& routes)
{
  std::set<std::string> sortedRoutes;
  for (const auto& r : routes)
    sortedRoutes.insert(r->GetName());

  std::vector<Node> nodes;
  for (const auto& rName : sortedRoutes)
  {
    nodes.push_back(rName);
  }
  return Node(nodes);
}

void Json::OutputStopResponseFormatter::ClearPreviousState()
{
  _responseNode.clear();
}

RequestType Json::InputBusResponseFormatter::GetType()
{
  return RequestType::InputBus;
}

Node Json::InputBusResponseFormatter::Format(const IResponse* response)
{
  return Node();
}


RequestType Json::InputStopResponseFormatter::GetType()
{
  return RequestType::InputStop;
}

Node Json::InputStopResponseFormatter::Format(const IResponse* response)
{
  return Node();
}

RequestType Json::FindRouteResponseFormatter::GetType()
{
  return RequestType::FindRoute;
}

Node Json::FindRouteResponseFormatter::Format(const IResponse* response)
{
  ClearPreviousState();
  auto r = dynamic_cast<const FindRouteResponse*>(response);
  if (r == nullptr)
    return {};

  if (!r->GetPath().has_value())
  {
    FormatRouteNotFound(r);
  }
  else
  {
    FormatRouteFound(r);
  }
  return Node(_responseNode);
}

void Json::FindRouteResponseFormatter::ClearPreviousState()
{
  _responseNode.clear();
}

void Json::FindRouteResponseFormatter::FormatRouteNotFound(const FindRouteResponse* r)
{
  FormatCommonPart(r);
  _responseNode.insert(std::make_pair("error_message", std::string("not found")));
}

void Json::FindRouteResponseFormatter::FormatRouteFound(const FindRouteResponse* r)
{
  FormatCommonPart(r);
  const auto& path = *r->GetPath();
  _responseNode.insert(std::make_pair("total_time", path.GetTotalTime()));

  std::vector<Node> items;
  BusItemData busItemData;

  const auto &elements = path.GetElements();
  for (const auto& e : elements)
  {
    if (e->GetType() == IPathElement::Wait)
    {
      if (busItemData.BusSpanCount != 0)
      {
        items.push_back(CreateBusItem(busItemData));
        busItemData = {};
      }

      auto waitElement = std::dynamic_pointer_cast<WaitPathElement>(e);
      if (waitElement)
        items.push_back(CreateWaitItem(*waitElement));
    }
    else if (e->GetType() == IPathElement::Bus)
    {
      auto busElement = std::dynamic_pointer_cast<BusPathElement>(e);
      if (busElement)
      {
        if (busItemData.BusName.empty())
          busItemData.BusName = busElement->GetBusName();
        busItemData.BusSpanCount++;
        busItemData.BusTotalTime += busElement->GetTime();
      }
    }
    else
    {
      assert(0);
    }
  }

  if (busItemData.BusSpanCount != 0)
  {
    items.push_back(CreateBusItem(busItemData));
  }
  _responseNode.insert(std::make_pair("items", items));
}

void Json::FindRouteResponseFormatter::FormatCommonPart(const FindRouteResponse* r)
{
  _responseNode["request_id"] = r->GetId();
}
Node Json::FindRouteResponseFormatter::CreateBusItem(const BusItemData& busItemData) const
{
  std::map<std::string, Node> busItem;
  busItem.insert(std::make_pair("type", std::string("Bus")));
  busItem.insert(std::make_pair("bus", busItemData.BusName));
  busItem.insert(std::make_pair("span_count", busItemData.BusSpanCount));
  busItem.insert(std::make_pair("time", busItemData.BusTotalTime));
  return busItem;
}

Node Json::FindRouteResponseFormatter::CreateWaitItem(const WaitPathElement& waitElement) const
{
  std::map<std::string, Node> waitItem =
  {
    std::make_pair("type", Node(std::string("Wait"))),
    std::make_pair("stop_name", Node(waitElement.GetStopName())),
    std::make_pair("time", Node(waitElement.GetTime()))
  };
  return waitItem;
}


Json::ResponseStreamFormatter::ResponseStreamFormatter() :
  _out(nullptr),
  _rootNode(),
  _formatters()
{
}

void Json::ResponseStreamFormatter::Start(std::ostream& out)
{
  _out = &out;
}

void Json::ResponseStreamFormatter::Format(const IResponse& response)
{
  auto formatterIt = _formatters.find(response.GetType());
  if (formatterIt == _formatters.end())
    return;

  const auto& formatter = formatterIt->second;
  auto node = formatter->Format(&response);
  if(!node.IsEmpty())
    _rootNode.push_back(std::move(node));
}

void Json::ResponseStreamFormatter::Finish()
{
  Document doc(_rootNode);
  (*_out) << doc.ToJson();
}

void Json::ResponseStreamFormatter::RegisterResponseFormatter(IResponseFormatterShp formatter)
{
  if (formatter != nullptr)
    _formatters[formatter->GetType()] = formatter;
}

