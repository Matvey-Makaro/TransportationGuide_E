#pragma once
#include <string>
#include <vector>
#include <optional>
#include <memory>

using StopNames = std::vector<std::string>;

class Route
{
public:
  enum Type
  {
    Common,
    Circular,
  };

  Route(std::string name);
  Route(std::string name, StopNames stops, Type type);

  const std::string& GetName() const;
  void SetName(std::string name);

  const StopNames& GetStopNames() const;
  void SetStopNames(StopNames stops);

  void AddStopName(std::string stopName);

  Type GetType() const;
  void SetType(Type type);

  StopNames GetFullRoute() const;
  int GetNumOfStopsInFullRoute() const;

private:
  StopNames GetFullRouteForCommon() const;
  StopNames GetFullRouteForCircle() const;

private:
  std::string _name;
  StopNames _stops;
  Type _type;
};

bool operator==(const Route& lhs, const Route& rhs);
bool operator!=(const Route& lhs, const Route& rhs);

using RouteShp = std::shared_ptr<Route>;
