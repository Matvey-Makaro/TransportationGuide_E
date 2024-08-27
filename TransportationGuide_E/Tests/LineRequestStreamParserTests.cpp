#include <sstream>
#include <vector>

#include "Tests/test_runner.h"
#include "CmpUtils.h"

#include "LineInputBusRequestParser.h"
#include "LineInputStopRequestParser.h"
#include "LineOutputBusRequestParser.h"
#include "LineOutputStopRequestParser.h"
#include "LineRequestStreamParser.h"

#include "InputBusRequest.h"
#include "InputStopRequest.h"
#include "OutputBusRequest.h"
#include "OutputStopRequest.h"


#include "LineRequestStreamParserTests.h"

using namespace std;
using namespace Line;
using namespace Line::Tests;

namespace
{
  RequestStreamParserShp GetDefaultParser()
  {
    auto inputBusRequestParser = make_shared<InputBusRequestParser>();
    auto inputStopRequestParser = make_shared<InputStopRequestParser>();
    auto outputBusRequestParser = make_shared<OutputBusRequestParser>();
    auto outputStopRequestParser = make_shared<OutputStopRequestParser>();

    RequestStreamParserShp streamParser = std::make_shared<RequestStreamParser>();
    streamParser->RegisterInputRequestsParser(inputBusRequestParser);
    streamParser->RegisterInputRequestsParser(inputStopRequestParser);
    streamParser->RegisterOutputRequestsParser(outputBusRequestParser);
    streamParser->RegisterOutputRequestsParser(outputStopRequestParser);

    return streamParser;
  }
}


void Line::Tests::NoRegParsersRequestStreamParserTest()
{
  stringstream in;
  in << "3\n"
    "Stop Tolstopaltsevo : 55.611087, 37.20829, 3900m to Marushkino\n"
    "Bus 750: Tolstopaltsevo - Marushkino - Rasskazovka\n"
    "Stop Rasskazovka : 55.632761, 37.333324\n"
    "2\n"
    "Bus 256\n"
    "Stop Samara\n";

  RequestStreamParserShp streamParser = std::make_shared<RequestStreamParser>();
  streamParser->SetRequestStream(in);
  std::vector<IRequestShp> requests;

  while (streamParser->HasRequest())
  {
    requests.push_back(streamParser->GetNextRequest());
  }

  size_t expectedSize = 5;

  ASSERT_EQUAL(requests.size(), expectedSize);
  ASSERT_EQUAL(requests[0], IRequestShp());
  ASSERT_EQUAL(requests[1], IRequestShp());
  ASSERT_EQUAL(requests[2], IRequestShp());
  ASSERT_EQUAL(requests[3], IRequestShp());
  ASSERT_EQUAL(requests[4], IRequestShp());
}

void Line::Tests::StreamRequestStreamParserTest2()
{
  stringstream in;
  in << "0\n"
    "2\n"
    "Bus 256\n"
    "Stop Samara\n";

  auto streamParser = GetDefaultParser();
  streamParser->SetRequestStream(in);
  std::vector<IRequestShp> requests;

  while (streamParser->HasRequest())
  {
    requests.push_back(streamParser->GetNextRequest());
  }

  size_t expectedSize = 2;

  OutputBusRequestShp expectedOutput1 = std::make_shared<OutputBusRequest>();
  expectedOutput1->SetName("256");

  OutputStopRequestShp expectedOutput2 = std::make_shared<OutputStopRequest>();
  expectedOutput2->SetName("Samara");


  ASSERT_EQUAL(requests.size(), expectedSize);

  {
    auto output1 = dynamic_pointer_cast<OutputBusRequest>(requests[0]);
    ASSERT(IsEqual(output1, expectedOutput1));
  }

  {
    auto output2 = dynamic_pointer_cast<OutputStopRequest>(requests[1]);
    ASSERT(IsEqual(output2, expectedOutput2));
  }
}

void Line::Tests::RequestStreamParserTest1()
{
  stringstream in;
  in << "3\n"
    "Stop Tolstopaltsevo : 55.611087, 37.20829, 3900m to Marushkino\n"
    "Bus 750: Tolstopaltsevo - Marushkino - Rasskazovka\n"
    "Stop Rasskazovka : 55.632761, 37.333324\n"
    "2\n"
    "Bus 256\n"
    "Stop Samara\n";

  auto streamParser = GetDefaultParser();
  streamParser->SetRequestStream(in);
  std::vector<IRequestShp> requests;

  while (streamParser->HasRequest())
  {
    requests.push_back(streamParser->GetNextRequest());
  }

  size_t expectedSize = 5;

  InputStopRequestShp expectedInput1 = std::make_shared<InputStopRequest>();
  expectedInput1->SetName("Tolstopaltsevo");
  expectedInput1->SetLatitude(55.611087);
  expectedInput1->SetLongitude(37.20829);
  expectedInput1->AddLengthToStop("Marushkino", 3900);

  InputBusRequestShp expectedInput2 = std::make_shared<InputBusRequest>();
  expectedInput2->SetName("750");
  StringVec stops = { "Tolstopaltsevo", "Marushkino", "Rasskazovka" };
  expectedInput2->SetStops(stops);
  expectedInput2->SetBusType(Route::Common);

  InputStopRequestShp expectedInput3 = std::make_shared<InputStopRequest>();
  expectedInput3->SetName("Rasskazovka");
  expectedInput3->SetLatitude(55.632761);
  expectedInput3->SetLongitude(37.333324);

  OutputBusRequestShp expectedOutput1 = std::make_shared<OutputBusRequest>();
  expectedOutput1->SetName("256");

  OutputStopRequestShp expectedOutput2 = std::make_shared<OutputStopRequest>();
  expectedOutput2->SetName("Samara");

 
  ASSERT_EQUAL(requests.size(), expectedSize);

  {
    auto input1 = dynamic_pointer_cast<InputStopRequest>(requests[0]);
    ASSERT(IsEqual(input1, expectedInput1));
  }
  
  {
    auto input2 = dynamic_pointer_cast<InputBusRequest>(requests[1]);
    ASSERT(IsEqual(input2, expectedInput2));
  }

  {
    auto input3 = dynamic_pointer_cast<InputStopRequest>(requests[2]);
    ASSERT(IsEqual(input3, expectedInput3));
  }

  {
    auto output1 = dynamic_pointer_cast<OutputBusRequest>(requests[3]);
    ASSERT(IsEqual(output1, expectedOutput1));
  }

  {
    auto output2 = dynamic_pointer_cast<OutputStopRequest>(requests[4]);
    ASSERT(IsEqual(output2, expectedOutput2));
  }
}
