#pragma once

#include "AbstractResponse.h"
#include "Route.h"

class OutputBusResponse : public AbstractOutputResponse
{
public:
  OutputBusResponse();

  const std::string& GetRouteName() const;
  void SetRouteName(std::string name);

  bool HasRoute() const;

  const RouteShp& GetRoute() const;
  void SetRoute(RouteShp route);

  int GetStopsOnRouteNum() const;
  void SetStopsOnRouteNum(int numOfStops);

  int GetUniqueStopsNum() const;
  void SetUniqueStopsNum(int num);

  double GetGeographicalRouteLength() const;
  void SetGeographicalRouteLength(double length);

  int GetRoadRouteLength() const;
  void SetRoadRouteLength(int length);

  double GetCurvature() const;
  void SetCurvature(double curvature);

private:
  RouteShp _route;
  int _stopsOnRouteNum;
  int _uniqueStopsNum;
  double _geographicalRouteLength;
  int _roadRouteLength;
  double _curvature;
  std::string _routeName;
};
using OutputBusResponseShp = std::shared_ptr<OutputBusResponse>;

