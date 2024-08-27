#pragma once
#include "IRequest.h"

class RoutingSettingsRequest : public IRequest
{
public:
  RoutingSettingsRequest();
  RoutingSettingsRequest(int busWaitTime, double busVelocity);
  virtual ~RoutingSettingsRequest() = default;

  RequestType GetType() const override;

  int GetBusWaitTime() const;
  void SetBusWaitTime(int time);

  double GetBusVelocity() const;
  void SetBusVelocity(double velocity);

private:
  int _busWaitTime;
  double _busVelocity;
};
using RoutingSettingsRequestShp = std::shared_ptr<RoutingSettingsRequest>;

