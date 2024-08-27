#include "Tests/test_runner.h"
#include "CmpUtils.h"
#include "Route.h"
#include "Stop.h"
#include "Database.h"
#include "InputStopRequest.h"
#include "InputStopResponse.h"
#include "InputStopRequestExecutor.h"
#include "InputStopRequestExecutorTests.h"

void InputStopRequestExecutorTypeTest()
{
  auto db = std::make_shared<Database>();
  InputStopRequestExecutor executor(db);
  ASSERT_EQUAL(executor.GetRequestType(), RequestType::InputStop);
}

void InputStopRequestExecutorStandardTest()
{
  auto db = std::make_shared<Database>();

  std::string stopName = "Tolstopaltsevo";
  double latitude = 55.61108;
  double longitude = 37.20829;

  auto request = std::make_shared<InputStopRequest>();
  request->SetName(stopName);
  request->SetLatitude(latitude);
  request->SetLongitude(longitude);

  InputStopRequestExecutor executor(db);
  auto r = executor.Execute(request.get());
  auto response = std::dynamic_pointer_cast<InputStopResponse>(r);
  auto stop = std::make_shared<Stop>();
  stop->name = stopName;
  stop->location = GeoPoint{ latitude, longitude };

  auto expectedResponse = std::make_shared<InputStopResponse>();
  auto expectedStop = db->GetStop(stopName);;
  
  ASSERT(IsEqual(response, expectedResponse));
  ASSERT(IsEqual(stop, expectedStop));
}

void InputStopRequestExecutorLongStopNameTest()
{
  auto db = std::make_shared<Database>();

  std::string stopName = "One two three foure five";
  double latitude = 55.61108;
  double longitude = 37.20829;

  auto request = std::make_shared<InputStopRequest>();
  request->SetName(stopName);
  request->SetLatitude(latitude);
  request->SetLongitude(longitude);

  InputStopRequestExecutor executor(db);
  auto r = executor.Execute(request.get());
  auto response = std::dynamic_pointer_cast<InputStopResponse>(r);
  auto stop = std::make_shared<Stop>();
  stop->name = stopName;
  stop->location = GeoPoint{ latitude, longitude };

  auto expectedResponse = std::make_shared<InputStopResponse>();
  auto expectedStop = db->GetStop(stopName);;

  ASSERT(IsEqual(response, expectedResponse));
  ASSERT(IsEqual(stop, expectedStop));
}

void InputStopRequestExecutorRoadLengthTest()
{
  auto db = std::make_shared<Database>();

  std::string stopName = "Tolstopaltsevo";
  double latitude = 55.61108;
  double longitude = 37.20829;
  std::string stop1Name = "stop1";
  int toStop1Length = 100;
  std::string stop2Name = "stop2";
  int toStop2Length = 30;

  auto request = std::make_shared<InputStopRequest>();
  request->SetName(stopName);
  request->SetLatitude(latitude);
  request->SetLongitude(longitude);
  request->AddLengthToStop(stop1Name, toStop1Length);
  request->AddLengthToStop(stop2Name, toStop2Length);

  InputStopRequestExecutor executor(db);
  auto r = executor.Execute(request.get());
  auto response = std::dynamic_pointer_cast<InputStopResponse>(r);
  auto stop = std::make_shared<Stop>();
  stop->name = stopName;
  stop->location = GeoPoint{ latitude, longitude };
  int resultToStop1Length = db->GetRoadLength(stopName, stop1Name);
  int resultToStop2Length = db->GetRoadLength(stopName, stop2Name);

  auto expectedResponse = std::make_shared<InputStopResponse>();
  auto expectedStop = db->GetStop(stopName);;

  ASSERT(IsEqual(response, expectedResponse));
  ASSERT(IsEqual(stop, expectedStop));
  ASSERT_EQUAL(resultToStop1Length, toStop1Length);
  ASSERT_EQUAL(resultToStop2Length, toStop2Length);
}


