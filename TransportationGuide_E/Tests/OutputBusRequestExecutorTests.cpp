#include "Tests/test_runner.h"
#include "CmpUtils.h"
#include "Database.h"
#include "Route.h"
#include "OutputBusRequest.h"
#include "OutputBusResponse.h"
#include "OutputBusRequestExecutor.h"
#include "OutputBusRequestExecutorTests.h"


void OutputBusRequestExecutorTypeTest()
{
  auto db = std::make_shared<Database>();
  OutputBusRequestExecutor executor(db);
  ASSERT_EQUAL(executor.GetRequestType(), RequestType::OutputBus);
}

void OutputBusRequestExecutorDefaultTest()
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

  auto request = std::make_shared<OutputBusRequest>();
  request->SetId(1);
  request->SetName(routeName);

  OutputBusRequestExecutor executor(db);
  auto r = executor.Execute(request.get());
  auto response = std::dynamic_pointer_cast<OutputBusResponse>(r);

  int expectedStopsOnRouteNum = 5;
  int expectedUniqueStopsNum = 3;
  int expectedRoadRouteLength = 100000;
  double expectedCurvature = 4.775667;

  ASSERT(response != nullptr);
  ASSERT_EQUAL(request->GetId(), response->GetId());
  ASSERT_EQUAL(response->GetRouteName(), route->GetName());
  ASSERT(IsEqual(response->GetRoute(), route));
  ASSERT_EQUAL(response->GetStopsOnRouteNum(), expectedStopsOnRouteNum);
  ASSERT_EQUAL(response->GetUniqueStopsNum(), expectedUniqueStopsNum);
  ASSERT_EQUAL(response->GetRoadRouteLength(), expectedRoadRouteLength);
  ASSERT(IsEqual(response->GetCurvature(), expectedCurvature));
}

void OutputBusRequestExecutorNotFoundTest()
{
  auto db = std::make_shared<Database>();
  std::string routeName = "750";
  auto request = std::make_shared<OutputBusRequest>();
  request->SetId(1);
  request->SetName(routeName);

  OutputBusRequestExecutor executor(db);
  auto r = executor.Execute(request.get());
  auto response = std::dynamic_pointer_cast<OutputBusResponse>(r);

  ASSERT(response != nullptr);
  ASSERT_EQUAL(request->GetId(), response->GetId());
  ASSERT_EQUAL(response->GetRouteName(), routeName);
  ASSERT(response->GetRoute() == nullptr);
}

