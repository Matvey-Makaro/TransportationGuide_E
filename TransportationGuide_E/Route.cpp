#include <unordered_set>
#include "Route.h"

using namespace std;

Route::Route(std::string name) :
  Route(std::move(name), {}, Type::Common)
{}

Route::Route(std::string name, StopNames stops, Route::Type type) :
  _name(std::move(name)),
  _stops(std::move(stops)), 
  _type(type)
{}

const std::string& Route::GetName() const
{
  return _name;
}

void Route::SetName(std::string name)
{
  _name = std::move(name);
}

const StopNames& Route::GetStopNames() const
{
  return _stops;
}

void Route::SetStopNames(StopNames stops)
{
  _stops = std::move(stops);
}

void Route::AddStopName(std::string stopName)
{
  _stops.push_back(std::move(stopName));
}

Route::Type Route::GetType() const
{
  return _type;
}

void Route::SetType(Type type)
{
  _type = type;
}

StopNames Route::GetFullRoute() const
{
  if (_type == Route::Common)
  {
    return GetFullRouteForCommon();
  }
  else
  {
    return GetFullRouteForCircle();
  }
}

int Route::GetNumOfStopsInFullRoute() const
{
  if (_type == Route::Common)
  {
    return _stops.size() * 2 - 1;
  }
  else
  {
    return _stops.size();
  }
}

StopNames Route::GetFullRouteForCommon() const
{
  StopNames fullRoute = _stops;
  fullRoute.reserve(GetNumOfStopsInFullRoute());
  for (auto it = std::next(_stops.crbegin()); it != _stops.crend(); it++)
    fullRoute.push_back(*it);
  return fullRoute;
}

StopNames Route::GetFullRouteForCircle() const
{
  return _stops;
}

bool operator==(const Route& lhs, const Route& rhs)
{
    return lhs.GetName() == rhs.GetName() &&
      lhs.GetType() == rhs.GetType() &&
      lhs.GetStopNames() == rhs.GetStopNames();
}

bool operator!=(const Route& lhs, const Route& rhs)
{
  return !(lhs == rhs);
}
