#include "OutputBusResponse.h"

OutputBusResponse::OutputBusResponse() :
  AbstractOutputResponse(RequestType::OutputBus),
  _route(nullptr),
  _stopsOnRouteNum(0),
  _uniqueStopsNum(0),
  _geographicalRouteLength(0.),
  _roadRouteLength(0),
  _curvature(0.),
  _routeName()
{
}

const std::string& OutputBusResponse::GetRouteName() const
{
  return _routeName;
}

void OutputBusResponse::SetRouteName(std::string name)
{
  _routeName = std::move(name);
}

bool OutputBusResponse::HasRoute() const
{
  return _route != nullptr;
}

const RouteShp& OutputBusResponse::GetRoute() const
{
  return _route;
}

void OutputBusResponse::SetRoute(RouteShp route)
{
  _route = std::move(route);
}

int OutputBusResponse::GetStopsOnRouteNum() const
{
  return _stopsOnRouteNum;
}

void OutputBusResponse::SetStopsOnRouteNum(int numOfStops)
{
  _stopsOnRouteNum = numOfStops;
}

int OutputBusResponse::GetUniqueStopsNum() const
{
  return _uniqueStopsNum;
}

void OutputBusResponse::SetUniqueStopsNum(int num)
{
  _uniqueStopsNum = num;
}

double OutputBusResponse::GetGeographicalRouteLength() const
{
  return _geographicalRouteLength;
}

void OutputBusResponse::SetGeographicalRouteLength(double length)
{
  _geographicalRouteLength = length;
}

int OutputBusResponse::GetRoadRouteLength() const
{
  return _roadRouteLength;
}

void OutputBusResponse::SetRoadRouteLength(int length)
{
  _roadRouteLength = length;
}

double OutputBusResponse::GetCurvature() const
{
  return _curvature;
}

void OutputBusResponse::SetCurvature(double curvature)
{
  _curvature = curvature;
}
