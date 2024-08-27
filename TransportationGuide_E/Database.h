#pragma once
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <string>
#include <optional>
#include <memory>
#include "Stop.h"
#include "Route.h"
#include "RoutingSettings.h"

using StringVec = std::vector<std::string>;
using StringViewVec = std::vector<std::string_view>;
using FromTo = std::pair<std::string_view, std::string_view>;


struct StopData
{
	StopShp Stop;
	std::vector<RouteShp> Routes;
};
using StopDataShp = std::shared_ptr<StopData>;


class Database
{
public:
  Database() = default;
  ~Database() = default;

  void AddStop(StopShp stop);
  void AddRoute(RouteShp route);

  RouteShp GetRoute(std::string_view routeName) const;
  StopShp GetStop(std::string_view stopName) const;
  std::vector<StopShp> GetStops(std::string_view routeName) const;
  std::vector<StopShp> GetFullRoute(std::string_view routeName) const;
  int GetNumOfStops(std::string_view routeName) const;
  int GetNumOfUniqueStops(std::string_view routeName) const;
  double GetGeographicalRouteLength(std::string_view routeName) const;
  int GetRoadRouteLength(std::string_view routeName) const;
  std::vector<RouteShp> GetRoutesByStop(std::string_view stopName) const;
  void SetRoadLength(std::string_view fromStop, std::string_view toStop, int length);
  int GetRoadLength(std::string_view fromStop, std::string_view toStop) const;

  std::vector<RouteShp> GetAllRoutes() const;
  size_t GetNumOfStops() const;

  const RoutingSettings& GetRoutingSettings() const;
  void SetRoutingSettings(const RoutingSettings& settings);

private:
  std::vector<StopShp> GetStops(const StringVec& stopNames) const;
  std::string_view AddStopName(std::string stopName);
  std::string_view AddRouteName(std::string routeName);
  StopDataShp AddStopData(std::string stopName);

private:
	std::unordered_set<std::string> _stopNames;
	std::unordered_set<std::string> _routeNames;
	std::unordered_map<std::string_view, StopDataShp> _nameToStopData;
	std::unordered_map<std::string_view, RouteShp> _nameToRoute;
	std::map<FromTo, int> _pathToRoadLength; // TODO: Change to unordered_map
  RoutingSettings _routingSettings;
};
using DatabaseShp = std::shared_ptr<Database>;
