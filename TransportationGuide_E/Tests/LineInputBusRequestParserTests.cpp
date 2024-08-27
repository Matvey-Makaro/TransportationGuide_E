#include <string>
#include <sstream>
#include <iomanip>
#include "Utiils.h"
#include "CmpUtils.h"
#include "LineInputBusRequestParser.h"
#include "InputBusRequest.h"
#include "Route.h"
#include "Tests/test_runner.h"
#include "Tests/LineInputBusRequestParserTests.h"

using namespace std;
using namespace Line;
using namespace Line::Tests;

void Line::Tests::InputBusRequestParserNameTest()
{
  InputBusRequestParser parser;
  string expectedName = "Bus";
  ASSERT_EQUAL(parser.GetRequestName(), expectedName);
}

void Line::Tests::InputBusRequestParserCommonRouteTest()
{
  std::string busName = "One two";
  StringVec stops = { "Biryulyovo Zapadnoye", "Biryusinka", "Universam", "Biryulyovo Tovarnaya" };
  Route::Type expectedType = Route::Type::Common;

  auto request = std::make_shared<InputBusRequest>();
  request->SetName(busName);
  request->SetStops(stops);
  request->SetBusType(expectedType);
  
  stringstream ss;
  ss << setprecision(6) << "Bus " << busName << ": ";
  string del = "-";
  for (size_t i = 0; i < stops.size(); i++)
  {
    if (i == stops.size() - 1)
      break;
    ss << stops[i] << " " << del << " ";
  }
  ss << stops.back();

  InputBusRequestParser parser;
  auto result = std::dynamic_pointer_cast<InputBusRequest>(parser.Parse(ss.str()));
  
  ASSERT(IsEqual(result, request));
}

void Line::Tests::InputBusRequestParserCircularRouteTest()
{
  std::string busName = "One two";
  StringVec stops = { "Biryulyovo Zapadnoye", "Biryusinka", "Universam", "Biryulyovo Tovarnaya" };
  Route::Type expectedType = Route::Type::Circular;

  auto request = std::make_shared<InputBusRequest>();
  request->SetName(busName);
  request->SetStops(stops);
  request->SetBusType(expectedType);

  stringstream ss;
  ss << setprecision(6) << "Bus " << busName << ": ";
  string del = ">";
  for (size_t i = 0; i < stops.size(); i++)
  {
    if (i == stops.size() - 1)
      break;
    ss << stops[i] << " " << del << " ";
  }
  ss << stops.back();

  InputBusRequestParser parser;
  auto result = std::dynamic_pointer_cast<InputBusRequest>(parser.Parse(ss.str()));

  ASSERT(IsEqual(result, request));
}

