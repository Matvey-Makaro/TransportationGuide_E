#include "Tests/test_runner.h"
#include "CmpUtils.h"
#include "OutputStopRequest.h"
#include "OutputStopResponse.h"
#include "Database.h"
#include "OutputStopRequestExecutor.h"
#include "OutputStopRequestExecutorTests.h"

void OutputStopRequestExecutorTypeTest()
{
  auto db = std::make_shared<Database>();
  OutputStopRequestExecutor executor(db);
  ASSERT_EQUAL(executor.GetRequestType(), RequestType::OutputStop)
}

void OutputStopRequestExecutordDefaultTest()
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

	std::string routeName1 = "bus1";
	StopNames expectedStopNames1 = { stop1->name, stop2->name };
	auto route1 = std::make_shared<Route>(routeName1);
	route1->SetType(Route::Common);
	route1->SetStopNames(expectedStopNames1);
	db->AddRoute(route1);


	std::string routeName2 = "bus2";
	StopNames expectedStopNames2 = { stop1->name, stop3->name };
	auto route2 = std::make_shared<Route>(routeName2);
	route2->SetType(Route::Common);
	route2->SetStopNames(expectedStopNames2);
	db->AddRoute(route2);

	auto request = std::make_shared<OutputStopRequest>();
	request->SetId(1);
	request->SetName(stop1->name);

	auto expectedResponse = std::make_shared<OutputStopResponse>();
	expectedResponse->SetId(request->GetId());
	expectedResponse->SetStopName(stop1->name);
	expectedResponse->SetStop(stop1);
	expectedResponse->SetRoutes({route1, route2});

	OutputStopRequestExecutor executor(db);
	auto r = executor.Execute(request.get());
	auto response = std::dynamic_pointer_cast<OutputStopResponse>(r);

	ASSERT(IsEqual(response, expectedResponse));
}

void OutputStopRequestExecutorNoBussesTest()
{
	auto db = std::make_shared<Database>();

	auto stop = std::make_shared<Stop>();
	stop->name = "Tolstopaltsevo";
	GeoPoint stop1Location;
	stop1Location.latitude = 55.611087;
	stop1Location.longitude = 37.20829;
	stop->location = stop1Location;
	db->AddStop(stop);

	auto request = std::make_shared<OutputStopRequest>();
	request->SetId(1);
	request->SetName(stop->name);

	auto expectedResponse = std::make_shared<OutputStopResponse>();
	expectedResponse->SetId(request->GetId());
	expectedResponse->SetStopName(stop->name);
	expectedResponse->SetStop(stop);
	expectedResponse->SetRoutes({});

	OutputStopRequestExecutor executor(db);
	auto r = executor.Execute(request.get());
	auto response = std::dynamic_pointer_cast<OutputStopResponse>(r);

	ASSERT(IsEqual(response, expectedResponse));
	ASSERT_EQUAL(request->GetId(), response->GetId());
}

void OutputStopRequestExecutorNotFoundTest()
{
	auto db = std::make_shared<Database>();

	auto stop = std::make_shared<Stop>();
	stop->name = "Tolstopaltsevo";
	GeoPoint stop1Location;
	stop1Location.latitude = 55.611087;
	stop1Location.longitude = 37.20829;
	stop->location = stop1Location;
	db->AddStop(stop);

	auto request = std::make_shared<OutputStopRequest>();
	request->SetId(0);
	std::string stopName = "Unknown stop";
	request->SetName(stopName);

	auto expectedResponse = std::make_shared<OutputStopResponse>();
	expectedResponse->SetStopName(stopName);
	expectedResponse->SetStop({});
	expectedResponse->SetRoutes({});

	OutputStopRequestExecutor executor(db);
	auto r = executor.Execute(request.get());
	auto response = std::dynamic_pointer_cast<OutputStopResponse>(r);

	ASSERT(IsEqual(response, expectedResponse));
}
