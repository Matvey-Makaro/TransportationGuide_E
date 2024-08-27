#include <sstream>
#include <iomanip>

#include "Tests/test_runner.h"
#include "CmpUtils.h"
#include "Database.h"
#include "OutputBusCommand.h"
#include "Stop.h"
#include "OutputBusCommandTests.h"

using namespace std;

void OutputBusCommandNameTest()
{
  auto db = std::make_shared<Database>();
  OutputBusCommand command(db);
  string expectedName = "Bus";
  ASSERT_EQUAL(command.GetName(), expectedName);
}

void OutputBusCommandDefaultTest()
{
  auto db = std::make_shared<Database>();

  auto stop1 = std::make_shared<Stop>();
  stop1->name = "Tolstopaltsevo";
  GeoPoint stop1Location;
  stop1Location.latitude = 55.611087;
  stop1Location.longitude = 37.20829;
  stop1->location = stop1Location;
  db->AddStop(stop1);

  auto stop2 = std::make_shared<Stop>();
  stop2->name = "Marushkino";
  GeoPoint stop2Location;
  stop2Location.latitude = 55.595884;
  stop2Location.longitude = 37.209755;
  stop2->location = stop2Location;
  db->AddStop(stop2);

  auto stop3 = std::make_shared<Stop>();
  stop3->name = "Rasskazovka";
  GeoPoint stop3Location;
  stop3Location.latitude = 55.632761;
  stop3Location.longitude = 37.333324;
  stop3->location = stop3Location;
  db->AddStop(stop3);
  
  std::string routeName = "750";
  StopNames expectedStopNames = { stop1->name, stop2->name, stop3->name };

  auto route = std::make_shared<Route>(routeName);
  route->SetType(Route::Common);
  route->SetStopNames(expectedStopNames);
  db->AddRoute(route);
  int expectedStop1Stop2Length = 45000;
  int expectedStop2Stop3Length = 5000;
  db->SetRoadLength(stop1->name, stop2->name, expectedStop1Stop2Length);
  db->SetRoadLength(stop2->name, stop3->name, expectedStop2Stop3Length);


  OutputBusCommand command(db);
  std::string commandStr = "Bus " + routeName;

  stringstream ss;
  ss << "Bus " << routeName << ": 5 stops on route, 3 unique stops, 100000 route length, 4.775667 curvature";
  string expectedResult = ss.str();

  command.Do(commandStr);

  ASSERT_EQUAL(command.GetResult(), expectedResult);
}

void OutputBusCommandNotFoundTest()
{
  auto db = std::make_shared<Database>();

  std::string routeName = "Bus 1";

  OutputBusCommand command(db);
  std::string commandStr = "Bus " + routeName;

  stringstream ss;
  ss << "Bus " << routeName << ": not found";
  string expectedResult = ss.str();

  command.Do(commandStr);

  ASSERT_EQUAL(command.GetResult(), expectedResult);
}