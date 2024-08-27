#include <cassert>
#include "Database.h"
#include "Utiils.h"
#include "InputBusCommand.h"

using namespace std;

namespace
{
  const std::unordered_map<std::string, Route::Type>& GetDelimiterToRouteType()
  {
    static const std::unordered_map<std::string, Route::Type> DelimiterToRouteType = {
    {"-", Route::Type::Common},
    {">", Route::Type::Circular},
    };
    return DelimiterToRouteType;
  }
  
  const std::unordered_map<Route::Type, std::string>& GetRouteTypeToDelimiter()
  {
    static const std::unordered_map<Route::Type, std::string> RouteTypeToDelimiter = []()
    {
      std::unordered_map<Route::Type, std::string> result;
      for (const auto& [del, type] : GetDelimiterToRouteType())
        result[type] = del;
      return result;
    }();
    return RouteTypeToDelimiter;
  }
}

const std::string InputBusCommand::Name = "Bus";

InputBusCommand::InputBusCommand(DatabaseShp db) : 
  _db(db)
{
}

const std::string& InputBusCommand::GetName() const
{
  return Name;
}

bool InputBusCommand::Do(const std::string& command)
{
  BaseCommandWithName::Do(command);

  auto route = std::make_shared<Route>(std::string(GetArgName()), GetStops(), GetRouteType());
  _db->AddRoute(route);
  return true;
}

Route::Type InputBusCommand::GetRouteType() const
{
  for (const auto& [del, type] : GetDelimiterToRouteType())
  {
    if (_commandStr->find(del) != _commandStr->npos)
      return type;
  }
  assert(0);
  return Route::Type::Common;
}

StringVec InputBusCommand::GetStops() const
{
  auto type = GetRouteType();
  auto del = GetRouteTypeToDelimiter().at(type);

  StringVec stops;
  string_view commandStrView = *_commandStr;
  auto [_, stopsStr] = SplitTwo(commandStrView, ":");

  while (!stopsStr.empty())
  {
    auto stopName = Strip(ReadToken(stopsStr, del));
    if (!stopName.empty())
      stops.push_back(std::string(stopName));
  }
  return stops;
}
