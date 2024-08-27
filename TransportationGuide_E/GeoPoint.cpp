#include <cmath>
#include "CmpUtils.h"
#include "Point.h"
#include "GeoPoint.h"

using namespace std;

constexpr double PI = 3.1415926535;
constexpr double EarthRadius = 6371000.;

namespace
{
  double ToRadians(double degrees)
  {
    return degrees * PI / 180.;
  }
}

double CalcDistance(const GeoPoint& p1, const GeoPoint& p2)
{
  using namespace std;

  GeoPoint p1Radians{ ToRadians(p1.latitude), ToRadians(p1.longitude) };
  GeoPoint p2Radians{ ToRadians(p2.latitude), ToRadians(p2.longitude) };

  double distance = acos(sin(p1Radians.latitude) * sin(p2Radians.latitude) +
    cos(p1Radians.latitude) * cos(p2Radians.latitude)*
    cos(abs(p1Radians.longitude - p2Radians.longitude))) * EarthRadius;
  return distance;
}

double CalcDistance(const GeoPointVec& points)
{
  double distance = 0.;
  for (size_t i = 0; i + 1 < points.size(); i++)
  {
    distance += CalcDistance(points[i], points[i + 1]);
  }
  return distance;
}

istream& operator>>(istream& in, GeoPoint& p)
{
  in >> p.latitude >> p.longitude;
  return in;
}

bool operator==(const GeoPoint& lhs, const GeoPoint& rhs)
{
  return IsEqual(lhs.latitude, rhs.latitude) &&
    IsEqual(lhs.longitude, rhs.longitude);
}

bool operator!=(const GeoPoint& lhs, const GeoPoint& rhs)
{
  return !(lhs == rhs);
}
