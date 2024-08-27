#include "Database.h"
#include "RoutingSettingsRequest.h"
#include "RoutingSettingsRequestExecutor.h"

RoutingSettingsRequestExecutor::RoutingSettingsRequestExecutor(DatabaseShp db) :
  _db(std::move(db))
{}

RequestType RoutingSettingsRequestExecutor::GetRequestType() const
{
  return RequestType::RoutingSettings;
}

IResponseShp RoutingSettingsRequestExecutor::Execute(const IRequest* request)
{
  auto r = ToRoutingSettingsRequest(request);
  if (r == nullptr)
    return {};

  RoutingSettings settings;
  settings.BusVelocityKmH = r->GetBusVelocity();
  settings.BusWaitTime = r->GetBusWaitTime();
  _db->SetRoutingSettings(settings);

  return {};
}

const RoutingSettingsRequest* RoutingSettingsRequestExecutor::ToRoutingSettingsRequest(const IRequest* request) const
{
  return dynamic_cast<const RoutingSettingsRequest*>(request);
}
