#include "SimpleRequestStreamParser.h"

using namespace std;
using namespace Line;

SimpleRequestStreamParser::SimpleRequestStreamParser() :
  _in(),
  _numOfRequests(0)
{}

void SimpleRequestStreamParser::SetRequestStream(std::istream& in)
{
  _in = in;
  _numOfRequests = GetNumOfRequests();
}

bool SimpleRequestStreamParser::HasRequest() const
{
  return _numOfRequests > 0;
}

IRequestShp SimpleRequestStreamParser::GetNextRequest() 
{
  if (_numOfRequests <= 0)
    return nullptr;

  auto requestStr = GetNextRequestStr();
  auto requestName = GetRequestName(requestStr);
  
  auto it = _parsers.find(std::string(requestName));
  if (it == _parsers.cend())
    return nullptr;
  const auto& parser = it->second;
  return parser->Parse(requestStr);
}

void SimpleRequestStreamParser::RegisterRequestsParser(IRequestParserShp parser)
{
  if (parser == nullptr)
    return;

  _parsers[parser->GetRequestName()] = std::move(parser);
}

std::string Line::SimpleRequestStreamParser::GetNextRequestStr()
{
  string commandStr;
  std::getline(_in.GetStream(), commandStr);
  _numOfRequests--;
  return commandStr;
}

std::string_view Line::SimpleRequestStreamParser::GetRequestName(std::string_view requestStr) const
{
  auto [commandName, _] = SplitTwo(requestStr);
  return commandName;
}

int Line::SimpleRequestStreamParser::GetNumOfRequests()
{
  string str;
  getline(_in.GetStream(), str);
  int numOfRequests = stoi(str);
  return numOfRequests;
}
