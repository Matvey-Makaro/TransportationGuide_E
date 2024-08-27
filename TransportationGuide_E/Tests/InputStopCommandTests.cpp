#include <sstream>
#include <iomanip>

#include "Tests/test_runner.h"
#include "CmpUtils.h"
#include "Database.h"
#include "InputStopCommand.h"
#include "InputStopCommandTests.h"

using namespace std;

void InputStopCommandNameTest()
{
  auto db = std::make_shared<Database>();
  InputStopCommand command(db);
  string expectedName = "Stop";
  ASSERT_EQUAL(command.GetName(), expectedName);
}

void InputStopCommandStandardTest()
{
  auto db = std::make_shared<Database>();
  InputStopCommand command(db);
  std::string stopName = "Tolstopaltsevo";
  double latitude = 55.61108;
  double longitude = 37.20829;
  stringstream ss;
  ss << setprecision(6) << "Stop " << stopName << ": " << latitude << ", " << longitude;
  string expectedResult;
  
  command.Do(ss.str());

  auto stop = db->GetStop(stopName);

  ASSERT(stop != nullptr);
  if (stop == nullptr)
    return;

  ASSERT_EQUAL(stop->name, stopName);
  ASSERT(IsEqual(stop->location.latitude, latitude));
  ASSERT(IsEqual(stop->location.longitude, longitude));
  ASSERT_EQUAL(command.GetResult(), expectedResult);
}

void InputStopCommandLongStopNameTest()
{
  auto db = std::make_shared<Database>();
  InputStopCommand command(db);
  std::string stopName = "One two three foure five";
  double latitude = 55.61108;
  double longitude = 37.20829;
  stringstream ss;
  ss << setprecision(6) << "Stop " << stopName << ": " << latitude << ", " << longitude;
  string expectedResult;

  command.Do(ss.str());

  auto stop = db->GetStop(stopName);

  ASSERT(stop != nullptr);
  if (stop == nullptr)
    return;

  ASSERT_EQUAL(stop->name, stopName);
  ASSERT(IsEqual(stop->location.latitude, latitude));
  ASSERT(IsEqual(stop->location.longitude, longitude));
  ASSERT_EQUAL(command.GetResult(), expectedResult);
}

void InputStopCommandTwoDoTest()
{
  auto db = std::make_shared<Database>();
  InputStopCommand command(db);

  std::string stopName1 = "Tolstopaltsevo";
  double latitude1 = 55.61108;
  double longitude1 = 37.20829;
  stringstream ss1;
  ss1 << setprecision(6) << "Stop " << stopName1 << ": " << latitude1 << ", " << longitude1;
  string expectedResult1;

  
  std::string stopName2 = "Hello world";
  double latitude2 = 25.61108;
  double longitude2 = 17.20829;
  stringstream ss2;
  ss2 << setprecision(6) << "Stop " << stopName2 << ": " << latitude2 << ", " << longitude2;
  string expectedResult2;
  
  command.Do(ss1.str());
  string result1 = command.GetResult();
  command.Do(ss2.str());
  string result2 = command.GetResult();

  auto stop1 = db->GetStop(stopName1);
  ASSERT(stop1 != nullptr);
  if (stop1 == nullptr)
    return;

  ASSERT_EQUAL(stop1->name, stopName1);
  ASSERT(IsEqual(stop1->location.latitude, latitude1));
  ASSERT(IsEqual(stop1->location.longitude, longitude1));
  ASSERT_EQUAL(result1, expectedResult1);

  auto stop2 = db->GetStop(stopName2);
  ASSERT(stop2 != nullptr);
  if (stop2 == nullptr)
    return;

  ASSERT_EQUAL(stop2->name, stopName2);
  ASSERT(IsEqual(stop2->location.latitude, latitude2));
  ASSERT(IsEqual(stop2->location.longitude, longitude2));
  ASSERT_EQUAL(result1, expectedResult2);
  
}

void InputStopCommandRoadLengthTest()
{
    auto db = std::make_shared<Database>();
    InputStopCommand command(db);
    std::string stopName = "Tolstopaltsevo";
    double latitude = 55.61108;
    double longitude = 37.20829;
    string stop1Name = "stop1";
    int toStop1Length = 100;
    string stop2Name = "stop2";
    int toStop2Length = 30;

    stringstream ss;
    ss << setprecision(6) << "Stop " << stopName << ": " << latitude << ", " << longitude << ", "
        << toStop1Length << "m to " << stop1Name << ", "
        << toStop2Length << "m to " << stop2Name;

    string expectedResult;

    command.Do(ss.str());

    auto stop = db->GetStop(stopName);
    int resultToStop1Length = db->GetRoadLength(stopName, stop1Name);
    int resultToStop2Length = db->GetRoadLength(stopName, stop2Name);

    ASSERT(stop != nullptr);
    if (stop == nullptr)
        return;

    ASSERT_EQUAL(stop->name, stopName);
    ASSERT(IsEqual(stop->location.latitude, latitude));
    ASSERT(IsEqual(stop->location.longitude, longitude));
    ASSERT_EQUAL(resultToStop1Length, toStop1Length);
    ASSERT_EQUAL(resultToStop2Length, toStop2Length);
    ASSERT_EQUAL(command.GetResult(), expectedResult);
}
