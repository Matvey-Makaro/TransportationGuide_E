#include <iomanip>
#include "Database.h"
#include "OutputBusCommand.h"

using namespace std;

const std::string OutputBusCommand::Name = "Bus";

OutputBusCommand::OutputBusCommand(DatabaseShp db) :
  _db(std::move(db))
{}

const std::string& OutputBusCommand::GetName() const
{
  return Name;
}

bool OutputBusCommand::Do(const std::string& command)
{
  BaseCommandWithName::Do(command);

  string name = std::string(GetArgName());
  auto route = _db->GetRoute(name);
  if (!route)
  {
    FormResultIfRouteNotExist(name);
    return true;
  }
  auto stopsOnRouteNum = _db->GetNumOfStops(name);
  auto uniqueStopsNum = _db->GetNumOfUniqueStops(name);
  auto geographicalRouteLength = _db->GetGeographicalRouteLength(name);
  auto roadRouteLength = _db->GetRoadRouteLength(name);
  double curvature = roadRouteLength / geographicalRouteLength;
  FormResult(name, stopsOnRouteNum, uniqueStopsNum, roadRouteLength, curvature);
  return true;
}

void OutputBusCommand::FormResultIfRouteNotExist(const std::string& routeName)
{
  _result << "Bus " + routeName + ": not found";
}

void OutputBusCommand::FormResult(const std::string& busName, 
    int stopsOnRouteNum, 
    int uniqueStopsNum, 
    double routeLength, 
    double curvature)
{
    _result << "Bus " << busName << ": "
        << stopsOnRouteNum << " stops on route, "
        << uniqueStopsNum << " unique stops, "
        << setprecision(6) << routeLength << " route length, "
        << setprecision(7) << curvature << " curvature";
}
