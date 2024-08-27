#include <unordered_set>
#include "Database.h"

using namespace std;

namespace
{
  GeoPointVec MapToGeoPointVec(const vector<StopShp>& stops)
  {
    GeoPointVec vec;
    vec.reserve(stops.size());
    for (const auto& s : stops)
      vec.push_back(s->location);
    return vec;
  }

  template<typename MapK, typename V, typename K>
  V GetByKey(const std::unordered_map<MapK, V>& m, const K& key)
  {
    auto it = m.find(key);
    if (it == m.cend())
      return {};
    return it->second;
  }

  string_view AddString(std::unordered_set<std::string>& s, std::string str)
  {
      auto [it, _] = s.insert(str);
      return *it;
  }

}

void Database::AddStop(StopShp stop)
{
  auto nameView = AddStopName(stop->name);
  auto stopData = AddStopData(stop->name);
  stopData->Stop = std::move(stop);
}

void Database::AddRoute(RouteShp route)
{
    // TODO: Тут нельзя использовать GetByKey, так как он возвращает результат по значению
    for (const auto& stop : route->GetStopNames())
    {
        auto stopData = AddStopData(stop);
        stopData->Routes.push_back(route);
    }
        
    auto nameView = AddRouteName(route->GetName());
    _nameToRoute[nameView] = std::move(route);
}

RouteShp Database::GetRoute(std::string_view routeName) const
{
  return GetByKey(_nameToRoute, routeName);
}

StopShp Database::GetStop(std::string_view stopName) const
{
  auto stopData = GetByKey(_nameToStopData, stopName);
  if (!stopData)
      return {};
  return stopData->Stop;
}

std::vector<StopShp> Database::GetStops(std::string_view routeName) const
{
  auto route = GetRoute(routeName);
  if (!route)
    return {};

  return GetStops(route->GetStopNames());
}

std::vector<StopShp> Database::GetFullRoute(std::string_view routeName) const
{
  auto route = GetRoute(routeName);
  if (!route)
    return {};

  return GetStops(route->GetFullRoute());
}

int Database::GetNumOfStops(std::string_view routeName) const
{
  auto route = GetRoute(routeName);
  if (route == nullptr)
    return 0;

  return route->GetNumOfStopsInFullRoute();
}

int Database::GetNumOfUniqueStops(std::string_view routeName) const
{
  auto route = GetRoute(routeName);
  if (route == nullptr)
    return 0;

  unordered_set<string> uniqueNames;
  for (const auto& name : route->GetStopNames())
    uniqueNames.insert(name);
  return static_cast<int>(uniqueNames.size());
}

double Database::GetGeographicalRouteLength(std::string_view routeName) const
{
  auto stops = GetFullRoute(routeName);
  auto points = MapToGeoPointVec(stops);
  return CalcDistance(points);
}

int Database::GetRoadRouteLength(std::string_view routeName) const
{
    auto stops = GetFullRoute(routeName);
    int result = 0;
    for (size_t i = 0; i + 1 < stops.size(); i++)
    {
        const auto& start = stops[i];
        const auto& finish = stops[i + 1];

        FromTo fromTo(start->name, finish->name);
        result += _pathToRoadLength.at(fromTo);
    }
    return result;
}

std::vector<RouteShp> Database::GetRoutesByStop(string_view stopName) const
{
    auto stopData = GetByKey(_nameToStopData, stopName);
    if (!stopData)
    {
        return {};
    }
    return stopData->Routes;
}

void Database::SetRoadLength(std::string_view fromStop, std::string_view toStop, int length)
{
    fromStop = AddStopName(string(fromStop));
    toStop = AddStopName(string(toStop));

    FromTo path(fromStop, toStop);
    _pathToRoadLength[path] = length;

    FromTo reversePath(toStop, fromStop);
    auto it = _pathToRoadLength.find(reversePath);
    if (it == _pathToRoadLength.end())
    {
        _pathToRoadLength[reversePath] = length;
    }
}

int Database::GetRoadLength(std::string_view fromStop, std::string_view toStop) const
{
    FromTo fromTo(fromStop, toStop);
    auto it = _pathToRoadLength.find(fromTo);
    if (it == _pathToRoadLength.end())
        return -1;
    return it->second;
}

std::vector<RouteShp> Database::GetAllRoutes() const
{
  std::vector<RouteShp> routes;
  routes.reserve(_nameToRoute.size());
  for (const auto& [name, route] : _nameToRoute)
  {
    routes.push_back(route);
  }
  return routes;
}

size_t Database::GetNumOfStops() const
{
  return _stopNames.size();
}

const RoutingSettings& Database::GetRoutingSettings() const
{
  return _routingSettings;
}

void Database::SetRoutingSettings(const RoutingSettings& settings)
{
  _routingSettings = settings;
}

std::vector<StopShp> Database::GetStops(const StringVec& stopNames) const
{
  vector<StopShp> stops;
  stops.reserve(stopNames.size());
  for (const auto& name : stopNames)
  {
    auto stop = GetStop(name);
    if (stop)
    {
      stops.push_back(stop);
    }
    else
    {
      std::cerr << "Database::GetStops() " << "stop is null for name: " << name;
    }
  }
  return stops;
}

std::string_view Database::AddStopName(std::string stopName)
{
    return AddString(_stopNames, std::move(stopName));
    
}

std::string_view Database::AddRouteName(std::string routeName)
{
    return AddString(_routeNames, std::move(routeName));
}

StopDataShp Database::AddStopData(std::string stopName)
{
    auto data = GetByKey(_nameToStopData, stopName);
    if (data)
        return data;
    auto nameView = AddStopName(stopName);
    data = std::make_shared<StopData>();
    _nameToStopData[nameView] = data;
    return data;
}



