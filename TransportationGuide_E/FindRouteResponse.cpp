#include "CmpUtils.h"
#include "FindRouteResponse.h"

FindRouteResponse::FindRouteResponse() :
  AbstractOutputResponse(RequestType::FindRoute)
{}

const std::optional<Path>& FindRouteResponse::GetPath() const
{
  return _path;
}

void FindRouteResponse::SetPath(std::optional<Path> path)
{
  _path = std::move(path);
}

bool operator==(const FindRouteResponse& lhs, const FindRouteResponse& rhs)
{
  return IsEqual(lhs.GetPath(), rhs.GetPath());
}

bool operator!=(const FindRouteResponse& lhs, const FindRouteResponse& rhs)
{
  return !(lhs == rhs);
}
