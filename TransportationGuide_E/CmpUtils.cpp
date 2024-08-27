#include <cmath>
#include "CmpUtils.h"

bool IsEqual(double lhs, double rhs, double eps)
{
  return std::fabs(lhs - rhs) <= eps;
}

