#include "OutputBusRequest.h"
#include "OutputBusResponse.h"
#include "Database.h"
#include "OutputBusRequestExecutor.h"

OutputBusRequestExecutor::OutputBusRequestExecutor(DatabaseShp db) :
  _db(std::move(db))
{}

RequestType OutputBusRequestExecutor::GetRequestType() const
{
  return RequestType::OutputBus;
}

IResponseShp OutputBusRequestExecutor::Execute(const IRequest* request)
{
  auto outputBusRequest = ToOutputBusRequest(request);
  if (outputBusRequest == nullptr)
    return {};

  auto response = std::make_shared<OutputBusResponse>();
  const auto& routeName = outputBusRequest->GetName();
  response->SetId(outputBusRequest->GetId());
  response->SetRouteName(routeName);
  response->SetRoute(_db->GetRoute(routeName));
  if (response->GetRoute() == nullptr)
  {
    return response;
  }

  auto stopsOnRouteNum = _db->GetNumOfStops(routeName);
  auto uniqueStopsNum = _db->GetNumOfUniqueStops(routeName);
  auto geographicalRouteLength = _db->GetGeographicalRouteLength(routeName);
  auto roadRouteLength = _db->GetRoadRouteLength(routeName);
  double curvature = roadRouteLength / geographicalRouteLength;

  response->SetStopsOnRouteNum(stopsOnRouteNum);
  response->SetUniqueStopsNum(uniqueStopsNum);
  response->SetGeographicalRouteLength(geographicalRouteLength);
  response->SetRoadRouteLength(roadRouteLength);
  response->SetCurvature(curvature);
  return response;
}

const OutputBusRequest* OutputBusRequestExecutor::ToOutputBusRequest(const IRequest* request) const
{
    return dynamic_cast<const OutputBusRequest*>(request);
}
