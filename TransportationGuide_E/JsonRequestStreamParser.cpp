#include "JsonUtils.h"
#include "IJsonRequestParser.h"
#include "JsonRequestStreamParser.h"

using namespace std;
using namespace Json;

namespace
{
  static const std::string& RoutingSettingsSectionName("routing_settings");
  static const std::string& BaseRequestsSectionName("base_requests");
  static const std::string& StatRequestsSectionName("stat_requests");

}

Json::Section::Section(std::string name, Node node) :
  Section(std::move(name), std::vector<Node>{std::move(node)})
{
}

Json::Section::Section(std::string name, std::vector<Node> nodes) :
  _nodes(std::move(nodes)),
  _currNodeIndex(0),
  _name(std::move(name))
{}

bool Json::Section::IsEnd() const
{
  return _currNodeIndex >= _nodes.size();
}

void Json::Section::ToNextNode()
{
  _currNodeIndex++;
}

const Node& Json::Section::GetCurrNode() const
{
  return _nodes[_currNodeIndex];
}

const std::string& Json::Section::GetName() const
{
  return _name;
}

Json::RequestStreamParser::RequestStreamParser() :
  _sections(),
  _routingSettingsParser(),
  _baseParsers(),
  _statParsers()
{}

void Json::RequestStreamParser::SetRequestStream(std::istream& in)
{
  ToStartState();
  auto doc = Load(in);
  const auto& rootNode = doc.GetRoot();
  AddRoutingSettingsSection(rootNode);
  AddBaseRequestsSection(rootNode);
  AddStatRequestsSection(rootNode);
  RemoveEmptySections();
}

bool Json::RequestStreamParser::HasRequest() const
{
  for (const auto& [section, _] : _sections)
  {
    if (!section.IsEnd())
      return true;
  }
  return false;
}

IRequestShp Json::RequestStreamParser::GetNextRequest()
{
  if (!HasRequest())
    return {};
  auto& [section, parseFunc] = _sections.front();
  IRequestShp request = parseFunc(section.GetCurrNode());
  section.ToNextNode();
  if (section.IsEnd())
  {
    if (section.GetName() == BaseRequestsSectionName)
      OnBaseRequestsParsed();
    _sections.pop_front();
  }
  return request;
}

void Json::RequestStreamParser::RegisterRoutingSettingsParser(IRequestParserShp parser)
{
  if (parser != nullptr)
    _routingSettingsParser = std::move(parser);
}

void Json::RequestStreamParser::RegisterInputRequestsParser(IRequestParserShp parser)
{
  if(parser != nullptr)
    _baseParsers[parser->GetRequestName()] = std::move(parser);
}

void Json::RequestStreamParser::RegisterOutputRequestsParser(IRequestParserShp parser)
{
  if (parser != nullptr)
    _statParsers[parser->GetRequestName()] = std::move(parser);
}

void RequestStreamParser::AddOnBaseRequestsParsedCb(OnBaseRequestsParsedCb cb)
{
  _onBaseRequestsParsedCbs.push_back(cb);
}

void Json::RequestStreamParser::ToStartState()
{
  _sections.clear();
}

void Json::RequestStreamParser::AddRoutingSettingsSection(const Node& rootNode)
{
  auto parseRoutingSettings = [this](const Node& node)
    {
      if (_routingSettingsParser == nullptr)
        return IRequestShp();
      return GetNextRequest(node, _routingSettingsParser);
    };
  _sections.emplace_back(
    Section(RoutingSettingsSectionName, GetObjByName(rootNode, RoutingSettingsSectionName)),
          parseRoutingSettings);
}

void Json::RequestStreamParser::AddBaseRequestsSection(const Node& rootNode)
{
  auto parseBaseRequest = [this](const Node& node)
    {
      return GetNextRequest(node, _baseParsers);
    };
  _sections.emplace_back(
    Section(BaseRequestsSectionName, GetArrByName(rootNode, BaseRequestsSectionName)), parseBaseRequest);
}

void Json::RequestStreamParser::AddStatRequestsSection(const Node& rootNode)
{
  auto parseStatRequest = [this](const Node& node)
    {
      return GetNextRequest(node, _statParsers);
    };
  _sections.emplace_back(
    Section(StatRequestsSectionName, GetArrByName(rootNode, StatRequestsSectionName)), parseStatRequest);
}

void Json::RequestStreamParser::RemoveEmptySections()
{
  _sections.remove_if([](const auto& section)
    {
      return section.first.IsEnd();
    });
}

std::vector<Node> Json::RequestStreamParser::GetArrByName(const Node& rootNode, const std::string& name) const
{
  if (!rootNode.IsMap())
    return {};
  const auto& dict = rootNode.AsMap();
  auto it = dict.find(name);
  if (it == dict.end())
    return {};

  auto arrNode = it->second;
  if (!arrNode.IsArray())
    return {};
  return arrNode.AsArray();
}

Node Json::RequestStreamParser::GetObjByName(const Node& rootNode, const std::string& name) const
{
  if (!rootNode.IsMap())
    return {};
  const auto& dict = rootNode.AsMap();
  auto it = dict.find(name);
  if (it == dict.end())
    return {};
  return it->second;
}

IRequestShp Json::RequestStreamParser::GetNextRequest(
  const Node& node,
  const std::unordered_map<std::string, IRequestParserShp>& parsers) const
{
  auto type = GetType(node);
  auto it = parsers.find(type);
  if (it == parsers.end())
    return {};
  return GetNextRequest(node, it->second);
}

IRequestShp Json::RequestStreamParser::GetNextRequest(
  const Node& node,
  const IRequestParserShp& parser) const
{
  return parser->Parse(node);
}

std::string Json::RequestStreamParser::GetType(const Node& node) const
{
  return GetStringByName(node, "type");
}

void RequestStreamParser::OnBaseRequestsParsed()
{
  for (const auto& cb : _onBaseRequestsParsedCbs)
    cb();
}
