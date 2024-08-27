#include "json.h"
#include "JsonUtils.h"

std::string Json::GetStringByName(const Node& node, const std::string& name)
{
  if (!node.IsMap())
    return {};
  const auto& dict = node.AsMap();
  auto it = dict.find(name);
  if (it == dict.end())
    return {};
  auto stringNode = it->second;
  if (!stringNode.IsString())
    return {};
  return stringNode.AsString();
}

double Json::GetDoubleByName(const Node& node, const std::string& name)
{
  if (!node.IsMap())
    return {};
  const auto& dict = node.AsMap();
  auto it = dict.find(name);
  if (it == dict.end())
    return {};
  auto doubleNode = it->second;
  if (!doubleNode.IsNumber())
    return {};
  return doubleNode.AsDouble();
}

int Json::GetIntByName(const Node& node, const std::string& name)
{
  if (!node.IsMap())
    return {};
  const auto& dict = node.AsMap();
  auto it = dict.find(name);
  if (it == dict.end())
    return {};
  auto intNode = it->second;
  if (!intNode.IsNumber())
    return {};
  return intNode.AsInt();
}

bool Json::GetBoolByName(const Node& node, const std::string& name)
{
  if (!node.IsMap())
    return {};
  const auto& dict = node.AsMap();
  auto it = dict.find(name);
  if (it == dict.end())
    return {};
  auto intNode = it->second;
  if (!intNode.IsBool())
    return {};
  return intNode.AsBool();
  return false;
}
