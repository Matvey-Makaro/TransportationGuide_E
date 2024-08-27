#include "RoutingSettingsRequest.h"

RoutingSettingsRequest::RoutingSettingsRequest() :
  RoutingSettingsRequest(0, 0.)
{}

RoutingSettingsRequest::RoutingSettingsRequest(int busWaitTime, double busVelocity) :
  _busWaitTime(busWaitTime),
  _busVelocity(busVelocity)
{}

RequestType RoutingSettingsRequest::GetType() const
{
  return RequestType::RoutingSettings;
}

int RoutingSettingsRequest::GetBusWaitTime() const
{
  return _busWaitTime;
}

void RoutingSettingsRequest::SetBusWaitTime(int time)
{
  _busWaitTime = time;
}

double RoutingSettingsRequest::GetBusVelocity() const
{
  return _busVelocity;
}

void RoutingSettingsRequest::SetBusVelocity(double velocity)
{
  _busVelocity = velocity;
}
