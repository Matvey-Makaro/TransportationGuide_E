#include "CmpUtils.h"
#include "OutputStopResponse.h"

OutputStopResponse::OutputStopResponse() : 
  AbstractOutputResponse(RequestType::OutputStop),
  _stopName(),
  _stop(nullptr),
  _routes()
{
}

const std::string& OutputStopResponse::GetStopName() const
{
  return _stopName;
}

void OutputStopResponse::SetStopName(std::string name)
{
  _stopName = std::move(name);
}

bool OutputStopResponse::IsStopExist() const
{
  return _stop != nullptr;
}

const StopShp& OutputStopResponse::GetStop() const
{
  return _stop;
}

void OutputStopResponse::SetStop(StopShp stop)
{
  _stop = std::move(stop);
}

bool OutputStopResponse::HasRoutes() const
{
  return !_routes.empty();
}

const std::vector<RouteShp>& OutputStopResponse::GetRoutes() const
{
  return _routes;
}

void OutputStopResponse::SetRoutes(std::vector<RouteShp> routes)
{
  _routes = std::move(routes);
}

bool operator==(const OutputStopResponse& lhs, const OutputStopResponse& rhs)
{
  return IsEqual(lhs.GetId(), rhs.GetId()) &&
    IsEqual(lhs.GetStopName(), rhs.GetStopName()) &&
    IsEqual(lhs.GetStop(), rhs.GetStop()) &&
    IsEqual(lhs.GetRoutes(), rhs.GetRoutes());
}

bool operator!=(const OutputStopResponse& lhs, const OutputStopResponse& rhs)
{
  return !(lhs == rhs);
}
