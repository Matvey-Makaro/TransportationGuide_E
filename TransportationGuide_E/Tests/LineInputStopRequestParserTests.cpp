#include <iomanip>
#include <sstream>
#include <string>
#include "Tests/test_runner.h"
#include "CmpUtils.h"
#include "InputStopRequest.h"
#include "LineInputStopRequestParser.h"
#include "Tests/LineInputStopRequestParserTests.h"

using namespace std;
using namespace Line;
using namespace Line::Tests;

void Line::Tests::InputStopRequestParserNameTest()
{
  string expectedName = "Stop";
  InputStopRequestParser parser;
  ASSERT_EQUAL(parser.GetRequestName(), expectedName);
}

void Line::Tests::InputStopRequestParserStandardTest()
{
  InputStopRequestShp request = std::make_shared<InputStopRequest>();
  request->SetName("Tolstopaltsevo");
  request->SetLatitude(55.61108);
  request->SetLongitude(37.20829);
  stringstream ss;
  ss << setprecision(6) << "Stop " << request->GetName() << ": " 
    << request->GetLatitude() << ", " << request->GetLongitude();

  InputStopRequestParser parser;
  auto result = std::dynamic_pointer_cast<InputStopRequest>(parser.Parse(ss.str()));

  ASSERT(IsEqual(result, request));
}

void Line::Tests::InputStopRequestParserLongStopNameTest()
{
  InputStopRequestShp request = std::make_shared<InputStopRequest>();
  request->SetName("One Two Three");
  request->SetLatitude(55.61108);
  request->SetLongitude(37.20829);
  stringstream ss;
  ss << setprecision(6) << "Stop " << request->GetName() << ": "
    << request->GetLatitude() << ", " << request->GetLongitude();

  InputStopRequestParser parser;
  auto result = std::dynamic_pointer_cast<InputStopRequest>(parser.Parse(ss.str()));

  ASSERT(IsEqual(result, request));
}

void Line::Tests::InputStopRequestParserRoadLengthTest()
{
  InputStopRequestShp request = std::make_shared<InputStopRequest>();
  request->SetName("One Two Three");
  request->SetLatitude(55.61108);
  request->SetLongitude(37.20829);
  string stop1Name = "stop1";
  int toStop1Length = 100;
  string stop2Name = "stop2";
  int toStop2Length = 30;
  request->AddLengthToStop(stop1Name, toStop1Length);
  request->AddLengthToStop(stop2Name, toStop2Length);
  stringstream ss;
  ss << setprecision(6) << "Stop " << request->GetName() << ": " 
    << request->GetLatitude() << ", " 
    << request->GetLongitude() << ", "
    << toStop1Length << "m to " << stop1Name << ", "
    << toStop2Length << "m to " << stop2Name;

  InputStopRequestParser parser;
  auto result = std::dynamic_pointer_cast<InputStopRequest>(parser.Parse(ss.str()));

  ASSERT(IsEqual(result, request));
}
