#include <sstream>
#include <string>
#include "Tests/test_runner.h"
#include "CmpUtils.h"
#include "OutputStopRequest.h"
#include "LineOutputStopRequestParser.h"
#include "LineOutputStopRequestParserTests.h"

using namespace std;
using namespace Line;
using namespace Line::Tests;

void Line::Tests::OutputStopRequestParserNameTest()
{
  string expectedName = "Stop";
  OutputStopRequestParser parser;
  ASSERT_EQUAL(parser.GetRequestName(), expectedName);
}

void Line::Tests::OutputStopRequestParserDefaultTest()
{
  auto request = make_shared<OutputStopRequest>();
  request->SetName("Hello world");
  std::string commandStr = "Stop " + request->GetName();
  OutputStopRequestParser parser;
  auto result = dynamic_pointer_cast<OutputStopRequest>(parser.Parse(commandStr));
  ASSERT(IsEqual(result, request));
}

