#include "Database.h"
#include "FindRouteRequest.h"
#include "FindRouteResponse.h"
#include "FindRouteRequestExecutor.h"
#include "PathSearcher.h"

FindRouteRequestExecutor::FindRouteRequestExecutor(DatabaseShp db, PathSearcherShp pathSearcher) :
  _db(std::move(db)),
  _pathSearcher(std::move(pathSearcher))
{
}

RequestType FindRouteRequestExecutor::GetRequestType() const
{
  return RequestType::FindRoute;
}

IResponseShp FindRouteRequestExecutor::Execute(const IRequest* request)
{
  auto findRouteRequest = dynamic_cast<const FindRouteRequest*>(request);
  if (findRouteRequest == nullptr)
    return {};

  auto response = std::make_shared<FindRouteResponse>();
  response->SetId(findRouteRequest->GetId());
  response->SetPath(
    _pathSearcher->FindPath(findRouteRequest->GetFromStop(), findRouteRequest->GetToStop()));
  return response;
}
