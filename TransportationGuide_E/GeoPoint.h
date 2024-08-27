#pragma once

#include <vector>
#include <iostream>

struct GeoPoint
{
  double latitude;
  double longitude;
};

using GeoPointVec = std::vector<GeoPoint>;

double CalcDistance(const GeoPoint& p1, const GeoPoint& p2);
double CalcDistance(const GeoPointVec& points);
std::istream& operator>>(std::istream& in, GeoPoint& p);
bool operator==(const GeoPoint& lhs, const GeoPoint& rhs);
bool operator!=(const GeoPoint& lhs, const GeoPoint& rhs);