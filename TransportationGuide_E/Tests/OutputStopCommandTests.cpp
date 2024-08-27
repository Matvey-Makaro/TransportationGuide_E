#include <sstream>
#include <iomanip>

#include "Tests/test_runner.h"
#include "CmpUtils.h"
#include "Database.h"
#include "OutputStopCommand.h"
#include "Stop.h"
#include "Route.h"
#include "OutputStopCommandTests.h"

using namespace std;

void OutputStopCommandNameTest()
{
	auto db = std::make_shared<Database>();
	OutputStopCommand command(db);
	string expectedName = "Stop";
	ASSERT_EQUAL(command.GetName(), expectedName);
}

void OutputStopCommandDefaultTest()
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
	StopNames expectedStopNames1 = { stop1->name, stop2->name};
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
	

	OutputStopCommand command(db);
	std::string commandStr = "Stop " + stop1->name;

	stringstream ss;
	ss << "Stop " << stop1->name << ": buses " << routeName1 << ' ' << routeName2;
	string expectedResult = ss.str();

	command.Do(commandStr);

	ASSERT_EQUAL(command.GetResult(), expectedResult);
}

void OutputStopCommandNoBussesTest()
{
	auto db = std::make_shared<Database>();

	auto stop = std::make_shared<Stop>();
	stop->name = "Tolstopaltsevo";
	GeoPoint stop1Location;
	stop1Location.latitude = 55.611087;
	stop1Location.longitude = 37.20829;
	stop->location = stop1Location;
	db->AddStop(stop);

	OutputStopCommand command(db);
	std::string commandStr = "Stop " + stop->name;

	stringstream ss;
	ss << "Stop " << stop->name << ": no buses";
	string expectedResult = ss.str();

	command.Do(commandStr);

	ASSERT_EQUAL(command.GetResult(), expectedResult);
}

void OutputStopCommandNotFoundTest()
{
	auto db = std::make_shared<Database>();

	auto stop = std::make_shared<Stop>();
	stop->name = "Tolstopaltsevo";
	GeoPoint stop1Location;
	stop1Location.latitude = 55.611087;
	stop1Location.longitude = 37.20829;
	stop->location = stop1Location;
	db->AddStop(stop);

	OutputStopCommand command(db);
	string unknownName = "unknownStop";
	std::string commandStr = "Stop " + unknownName;

	stringstream ss;
	ss << "Stop " << unknownName << ": not found";
	string expectedResult = ss.str();

	command.Do(commandStr);

	ASSERT_EQUAL(command.GetResult(), expectedResult);
}
