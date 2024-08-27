#include <string>
#include "json.h"
#include "JsonUtils.h"
#include "JsonAbstractRequestParser.h"

using namespace Json;
using namespace std;

std::string Json::AbstractRequestParser::GetStringByName(const Node& node, const std::string& name) const
{
  return ::GetStringByName(node, name);
}

double Json::AbstractRequestParser::GetDoubleByName(const Node& node, const std::string& name) const
{
  return ::GetDoubleByName(node, name);
}

int Json::AbstractRequestParser::GetIntByName(const Node& node, const std::string& name) const
{
  return ::GetIntByName(node, name);
}

bool Json::AbstractRequestParser::GetBoolByName(const Node& node, const std::string& name) const
{
  return ::GetBoolByName(node, name);
}
