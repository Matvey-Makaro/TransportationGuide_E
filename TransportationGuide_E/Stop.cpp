#include "Stop.h"

using namespace std;

bool operator==(const Stop& lhs, const Stop& rhs)
{
  return lhs.name == rhs.name &&
    lhs.location == rhs.location;
}

bool operator!=(const Stop& lhs, const Stop& rhs)
{
  return !(lhs == rhs);
}
