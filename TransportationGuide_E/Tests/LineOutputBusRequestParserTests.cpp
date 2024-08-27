#include <iomanip>
#include <sstream>
#include <string>
#include "Tests/test_runner.h"
#include "CmpUtils.h"
#include "OutputBusRequest.h"
#include "LineOutputBusRequestParser.h"
#include "LineOutputBusRequestParserTests.h"

using namespace std;
using namespace Line;
using namespace Line::Tests;

void Line::Tests::OutputBusRequestParserNameTest()
{
  string expectedName = "Bus";
  OutputBusRequestParser parser;
  ASSERT_EQUAL(parser.GetRequestName(), expectedName);
}

void Line::Tests::OutputBusRequestParserDefaultTest()
{
  auto request = make_shared<OutputBusRequest>();
  request->SetName("Hello world");
  std::string commandStr = "Bus " + request->GetName();
  OutputBusRequestParser parser;
  auto result = dynamic_pointer_cast<OutputBusRequest>(parser.Parse(commandStr));
  ASSERT(IsEqual(result, request));
}

