#include <cmath>
#include "test_runner.h"
#include "CmpUtils.h"
#include "GeoPointTests.h"
#include "GeoPoint.h"



void CalcDistanceSimpleTest()
{
  GeoPoint p1{55.611087, 37.20829 };
  GeoPoint p2{55.595884, 37.209755 };
  GeoPoint p3{55.632761, 37.333324 };

  double distance = (CalcDistance(p1, p2) + CalcDistance(p2, p3)) * 2;
  double expectedDistance = 20939.483;
  ASSERT(IsEqual(distance, expectedDistance));
}
