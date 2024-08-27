#include "Tests/test_runner.h"
#include "CmpUtils.h"
#include "InputBusRequest.h"
#include "InputBusResponse.h"
#include "Database.h"
#include "InputBusRequestExecutor.h"
#include "InputBusRequestExecutorTests.h"

void InputBusRequestExecutorTypeTest()
{
  auto db = std::make_shared<Database>();
  InputBusRequestExecutor executor(db);
  ASSERT_EQUAL(executor.GetRequestType(), RequestType::InputBus);
}

void InputBusRequestExecutorCommonRouteTest()
{
  auto db = std::make_shared<Database>();

  std::string busName = "One two";
  StringVec stops = { "Biryulyovo Zapadnoye", "Biryusinka", "Universam", "Biryulyovo Tovarnaya" };
  Route::Type routeType = Route::Type::Common;

  auto request = std::make_shared<InputBusRequest>();
  request->SetName(busName);
  request->SetStops(stops);
  request->SetBusType(routeType);

  InputBusRequestExecutor executor(db);
  IResponseShp response = executor.Execute(request.get());
  auto r = std::dynamic_pointer_cast<InputBusResponse>(response);
  auto route = db->GetRoute(busName);

  auto expectedResponse = std::make_shared<InputBusResponse>();
  auto expectedRoute = std::make_shared<Route>(busName, stops, routeType);

  ASSERT(IsEqual(r, expectedResponse));
  ASSERT(IsEqual(route, expectedRoute));
}

void InputBusRequestExecutorCircularRouteTest()
{
  auto db = std::make_shared<Database>();

  std::string busName = "One two";
  StringVec stops = { "Biryulyovo Zapadnoye", "Biryusinka", "Universam", "Biryulyovo Tovarnaya" };
  Route::Type routeType = Route::Type::Circular;

  auto request = std::make_shared<InputBusRequest>();
  request->SetName(busName);
  request->SetStops(stops);
  request->SetBusType(routeType);

  InputBusRequestExecutor executor(db);
  IResponseShp response = executor.Execute(request.get());
  auto r = std::dynamic_pointer_cast<InputBusResponse>(response);
  auto route = db->GetRoute(busName);

  auto expectedResponse = std::make_shared<InputBusResponse>();
  auto expectedRoute = std::make_shared<Route>(busName, stops, routeType);

  ASSERT(IsEqual(r, expectedResponse));
  ASSERT(IsEqual(route, expectedRoute));
}
