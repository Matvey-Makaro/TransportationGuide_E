#include "InputBusRequest.h"
#include "InputBusResponse.h"
#include "Database.h"
#include "Route.h"
#include "InputBusRequestExecutor.h"

InputBusRequestExecutor::InputBusRequestExecutor(DatabaseShp db) :
  _db(std::move(db))
{
}

RequestType InputBusRequestExecutor::GetRequestType() const
{
  return RequestType::InputBus;
}

IResponseShp InputBusRequestExecutor::Execute(const IRequest* request)
{
  auto r = ToInputBusRequest(request);
  if (r == nullptr)
    return {};

  auto route = std::make_shared<Route>(r->GetName(), r->GetStops(), r->GetBusType());
  _db->AddRoute(std::move(route));

  auto response = std::make_shared<InputBusResponse>();
  return response;
}

const InputBusRequest* InputBusRequestExecutor::ToInputBusRequest(const IRequest* request) const
{
  return dynamic_cast<const InputBusRequest*>(request);
}
