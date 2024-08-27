#include "FindRouteRequest.h"

RequestType FindRouteRequest::GetType() const
{
    return RequestType::FindRoute;
}

const std::string& FindRouteRequest::GetFromStop() const
{
  return _fromStop;
}

void FindRouteRequest::SetFromStop(std::string name)
{
  _fromStop = std::move(name);
}

const std::string& FindRouteRequest::GetToStop() const
{
  return _toStop;
}

void FindRouteRequest::SetToStop(std::string name)
{
  _toStop = std::move(name);
}

bool operator==(const FindRouteRequest& lhs, const FindRouteRequest& rhs)
{
  return lhs.GetFromStop() == rhs.GetFromStop() &&
    lhs.GetToStop() == rhs.GetToStop();
}

bool operator!=(const FindRouteRequest& lhs, const FindRouteRequest& rhs)
{
  return !(lhs == rhs);
}
