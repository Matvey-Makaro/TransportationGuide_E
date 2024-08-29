#pragma once
#include <memory>
#include <string>
#include <iostream>
#include "GeoPoint.h"

struct Stop
{
  std::string name;
  GeoPoint location;
};
using StopShp = std::shared_ptr<Stop>;

bool operator==(const Stop& lhs, const Stop& rhs);
bool operator!=(const Stop& lhs, const Stop& rhs);
