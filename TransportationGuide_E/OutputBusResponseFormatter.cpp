#include <sstream>
#include <iomanip>
#include "OutputBusResponse.h"
#include "OutputBusResponseFormatter.h"
#include "JsonResponseFormatters.h"

using namespace std;
using namespace Line;

RequestType OutputBusResponseFormatter::GetType()
{
  return RequestType::OutputBus;
}

std::string OutputBusResponseFormatter::Format(const IResponse* response)
{
  auto r = dynamic_cast<const OutputBusResponse*>(response);
  if (r == nullptr)
    return {};

  if (r->GetRoute() == nullptr)
  {
    return FormatIfRouteNotFound(r);
  }
  return DefaultFormat(r);
}

std::string Line::OutputBusResponseFormatter::FormatIfRouteNotFound(const OutputBusResponse* r) const
{
  std::stringstream ss;
  ss << "Bus " + r->GetRouteName() + ": not found";
  return ss.str();
}

std::string Line::OutputBusResponseFormatter::DefaultFormat(const OutputBusResponse* r) const
{
  std::stringstream ss;

  ss << "Bus " << r->GetRouteName() << ": "
    << r->GetStopsOnRouteNum() << " stops on route, "
    << r->GetUniqueStopsNum() << " unique stops, "
    << setprecision(6) << r->GetRoadRouteLength() << " route length, "
    << setprecision(7) << r->GetCurvature() << " curvature";

  return ss.str();
}
