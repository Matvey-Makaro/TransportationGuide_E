#include "InputStopRequest.h"
#include "InputStopResponse.h"
#include "Database.h"
#include "InputStopRequestExecutor.h"

InputStopRequestExecutor::InputStopRequestExecutor(DatabaseShp db) :
  _db(std::move(db))
{
}

RequestType InputStopRequestExecutor::GetRequestType() const
{
  return RequestType::InputStop;
}

IResponseShp InputStopRequestExecutor::Execute(const IRequest* request)
{
  auto r = ToInputStopRequest(request);

  auto stop = std::make_shared<Stop>();
  stop->name = r->GetName();
  stop->location = GeoPoint{r->GetLatitude(), r->GetLongitude()};
  _db->AddStop(std::move(stop));

  for (const auto& [toStop, length] : r->GetStopToLength())
  {
    _db->SetRoadLength(r->GetName(), toStop, length);
  }

  auto response = std::make_shared<InputStopResponse>();
  return response;
}

const InputStopRequest* InputStopRequestExecutor::ToInputStopRequest(const IRequest* request) const
{
  return dynamic_cast<const InputStopRequest*>(request);
}
