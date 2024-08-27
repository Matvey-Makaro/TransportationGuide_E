#pragma once

#include <cstdint>
#include <memory>

struct RoutingSettings
{
public:
  RoutingSettings() = default;
  ~RoutingSettings() = default;
  uint32_t BusWaitTime{ 0 };
  double BusVelocityKmH{0.};
};
