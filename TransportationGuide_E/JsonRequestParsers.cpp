#include <string>
#include "OutputBusRequest.h"
#include "OutputStopRequest.h"
#include "InputBusRequest.h"
#include "InputStopRequest.h"
#include "RoutingSettingsRequest.h"
#include "FindRouteRequest.h"
#include "json.h"
#include "JsonRequestParsers.h"

using namespace Json;
using namespace std;

const std::string& Json::OutputBusRequestParser::GetRequestName() const
{
  static string name = "Bus";
  return name;
}

IRequestShp Json::OutputBusRequestParser::Parse(const Node& node)
{
  if (!node.IsMap())
    return {};

  auto request = std::make_shared<OutputBusRequest>();
  request->SetId(GetId(node));
  request->SetName(GetName(node));
  return request;
}

int Json::OutputBusRequestParser::GetId(const Node& node) const
{
  return GetIntByName(node, "id");
}

std::string Json::OutputBusRequestParser::GetName(const Node& node) const
{
  return GetStringByName(node, "name");
}


const std::string& Json::OutputStopRequestParser::GetRequestName() const
{
  static string name = "Stop";
  return name;
}

IRequestShp Json::OutputStopRequestParser::Parse(const Node& node)
{
  if (!node.IsMap())
    return {};

  auto request = std::make_shared<OutputStopRequest>();
  request->SetId(GetId(node));
  request->SetName(GetName(node));
  return request;
}

int Json::OutputStopRequestParser::GetId(const Node& node) const
{
  return GetIntByName(node, "id");
}

std::string Json::OutputStopRequestParser::GetName(const Node& node) const
{
  return GetStringByName(node, "name");
}



const std::string& Json::InputBusRequestParser::GetRequestName() const
{
  static string name = "Bus";
  return name;
}

IRequestShp Json::InputBusRequestParser::Parse(const Node& node)
{
  if (!node.IsMap())
    return {};

  auto request = std::make_shared<InputBusRequest>();
  request->SetName(GetName(node));
  request->SetStops(GetStops(node));
  request->SetBusType(GetRouteType(node));
  return request;
}

std::string Json::InputBusRequestParser::GetName(const Node& node) const
{
  return GetStringByName(node, "name");
}

StringVec Json::InputBusRequestParser::GetStops(const Node& node) const
{
  if (!node.IsMap())
    return {};
  const auto& dict = node.AsMap();
  auto it = dict.find("stops");
  if (it == dict.end())
    return {};

  auto arrNode = it->second;
  if (!arrNode.IsArray())
    return {};
  auto arr = arrNode.AsArray();
  StringVec stops;
  stops.reserve(arr.size());
  for (const auto& n : arr)
  {
    if (!n.IsString())
      continue;
    stops.push_back(n.AsString());
  }
  return stops;
}

Route::Type Json::InputBusRequestParser::GetRouteType(const Node& node) const
{
  bool is_roundtrip = GetBoolByName(node, "is_roundtrip");
  return is_roundtrip ? Route::Circular : Route::Common;
}



const std::string& Json::InputStopRequestParser::GetRequestName() const
{
  static string name = "Stop";
  return name;
}

IRequestShp Json::InputStopRequestParser::Parse(const Node& node)
{
  if (!node.IsMap())
    return {};

  auto request = std::make_shared<InputStopRequest>();
  request->SetName(GetName(node));
  request->SetStopToLength(GetRoadToDistance(node));
  request->SetLongitude(GetLongitude(node));
  request->SetLatitude(GetLatitude(node));
  
  return request;
}

std::string Json::InputStopRequestParser::GetName(const Node& node) const
{
  return GetStringByName(node, "name");
}

std::unordered_map<std::string, int> Json::InputStopRequestParser::GetRoadToDistance(const Node& node) const
{
  if (!node.IsMap())
    return {};
  const auto& dict = node.AsMap();
  auto it = dict.find("road_distances");
  if (it == dict.end())
    return {};

  auto mapNode = it->second;
  if (!mapNode.IsMap())
    return {};
  auto nameToNodes = mapNode.AsMap();
  std::unordered_map<std::string, int> roadToDistance;
  for (const auto& [name, node] : nameToNodes)
  {
    if (!node.IsInt())
      continue;
    roadToDistance[name] = node.AsInt();
  }

  return roadToDistance;
}

double Json::InputStopRequestParser::GetLongitude(const Node& node) const
{
  return GetDoubleByName(node, "longitude");
}

double Json::InputStopRequestParser::GetLatitude(const Node& node) const
{
  return GetDoubleByName(node, "latitude");
}

const std::string& Json::InputRoutingSettingsParser::GetRequestName() const
{
  static string name = "routing_settings";
  return name;
}

IRequestShp Json::InputRoutingSettingsParser::Parse(const Node& node)
{
  if (!node.IsMap())
    return {};

  auto request = std::make_shared<RoutingSettingsRequest>();
  request->SetBusVelocity(GetDoubleByName(node, "bus_velocity"));
  request->SetBusWaitTime(GetIntByName(node, "bus_wait_time"));
  return request;
}

const std::string& FindRouteRequestParser::GetRequestName() const
{
  static string name = "Route";
  return name;
}

IRequestShp FindRouteRequestParser::Parse(const Node& node)
{
  if (!node.IsMap())
    return {};

  auto request = std::make_shared<FindRouteRequest>();
  request->SetId(GetId(node));
  request->SetFromStop(GetFrom(node));
  request->SetToStop(GetTo(node));
  return request;
}

int FindRouteRequestParser::GetId(const Node& node) const
{
  return GetIntByName(node, "id");
}

std::string FindRouteRequestParser::GetFrom(const Node& node) const
{
  return GetStringByName(node, "from");
}

std::string FindRouteRequestParser::GetTo(const Node& node) const
{
  return GetStringByName(node, "to");
}
