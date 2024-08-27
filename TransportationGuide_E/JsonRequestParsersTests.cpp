#include <string>
#include <sstream>
#include <unordered_map>
#include "Tests/test_runner.h"
#include "CmpUtils.h"
#include "JsonRequestParsers.h"
#include "OutputBusRequest.h"
#include "OutputStopRequest.h"
#include "InputBusRequest.h"
#include "InputStopRequest.h"
#include "JsonRequestStreamParser.h"
#include "json.h"
#include "JsonRequestParsersTests.h"

using namespace std;
using namespace Json::Tests;
using namespace Json;

void Json::Tests::OutputBusRequestParserNameTest()
{
  string expectedName = "Bus";
  OutputBusRequestParser parser;
  ASSERT_EQUAL(parser.GetRequestName(), expectedName);
}

void Json::Tests::OutputBusRequestParserDefaultTest()
{
  stringstream ss;
  ss << "{\n";
  ss << "\"type\": \"Bus\"\n,";
  ss << "\"name\" : \"Biryulyovo Zapadnoye\"\n,";
  ss << "\"id\" : 1042838872\n";
  ss << "}";

  auto doc = Load(ss);

  OutputBusRequestParser parser;
  auto r = parser.Parse(doc.GetRoot());
  auto request = dynamic_pointer_cast<OutputBusRequest>(r);

  auto expectedRequest = std::make_shared<OutputBusRequest>();
  expectedRequest->SetId(1042838872);
  expectedRequest->SetName("Biryulyovo Zapadnoye");

  ASSERT(IsEqual(request, expectedRequest));
}

void Json::Tests::OutputStopRequestParserNameTest()
{
  string expectedName = "Stop";
  OutputStopRequestParser parser;
  ASSERT_EQUAL(parser.GetRequestName(), expectedName);
}

void Json::Tests::OutputStopRequestParserDefaultTest()
{
  stringstream ss;
  ss << "{\n";
  ss << "\"type\": \"Stop\"\n,";
  ss << "\"name\" : \"Biryulyovo Zapadnoye\"\n,";
  ss << "\"id\" : 1042838872\n";
  ss << "}";

  auto doc = Load(ss);

  OutputStopRequestParser parser;
  auto r = parser.Parse(doc.GetRoot());
  auto request = dynamic_pointer_cast<OutputStopRequest>(r);

  auto expectedRequest = std::make_shared<OutputStopRequest>();
  expectedRequest->SetId(1042838872);
  expectedRequest->SetName("Biryulyovo Zapadnoye");

  ASSERT(IsEqual(request, expectedRequest));
}


void Json::Tests::InputBusRequestParserNameTest()
{
  string expectedName = "Bus";
  InputBusRequestParser parser;
  ASSERT_EQUAL(parser.GetRequestName(), expectedName);
}

void Json::Tests::InputBusRequestParserDefaultTest()
{
  stringstream ss;
  ss << "{\n";
  ss << "\"type\": \"Bus\"\n,";
  ss << "\"name\" : \"Biryulyovo Zapadnoye\"\n,";
  ss << "\"stops\": [\n";
  ss << "\"Biryulyovo Zapadnoye\",\n";
  ss << "\"Biryusinka\",\n";
  ss << "\"Universam\",\n";
  ss << "\"Biryulyovo Tovarnaya\",\n";
  ss << "\"Biryulyovo Passazhirskaya\",\n";
  ss << "\"Biryulyovo Zapadnoye\"\n";
  ss << "],\n";
  ss << "\"is_roundtrip\": true\n";
  ss << "}";

  auto doc = Load(ss);

  InputBusRequestParser parser;
  auto r = parser.Parse(doc.GetRoot());
  auto request = dynamic_pointer_cast<InputBusRequest>(r);

  std::string name = "Biryulyovo Zapadnoye";
  StringVec stops = {
    "Biryulyovo Zapadnoye",
    "Biryusinka",
    "Universam",
    "Biryulyovo Tovarnaya",
    "Biryulyovo Passazhirskaya",
    "Biryulyovo Zapadnoye",
  };
  Route::Type busType = Route::Circular;

  auto expectedRequest = std::make_shared<InputBusRequest>();
  expectedRequest->SetName(name);
  expectedRequest->SetStops(stops);
  expectedRequest->SetBusType(busType);

  ASSERT(IsEqual(request, expectedRequest));
}

void Json::Tests::InputStopRequestParserNameTest()
{
  string expectedName = "Stop";
  InputStopRequestParser parser;
  ASSERT_EQUAL(parser.GetRequestName(), expectedName);
}

void Json::Tests::InputStopRequestParserDefaultTest()
{
  stringstream ss;
  ss << "{\n";
  ss << "\"type\": \"Stop\"\n,";
  ss << "\"name\" : \"Biryulyovo Zapadnoye\"\n,";
  ss << "\"road_distances\": {\n";
  ss << "\"Rossoshanskaya ulitsa\": 7500,\n";
  ss << "\"Biryusinka\" : 1800,\n";
  ss << "\"Universam\" : 2400\n";
  ss << "},\n";
  ss << "\"longitude\" : 37.6517,\n";
  ss << "\"latitude\" : 55.574371\n";
  ss << "}";

  auto doc = Load(ss);

  InputStopRequestParser parser;
  auto r = parser.Parse(doc.GetRoot());
  auto request = dynamic_pointer_cast<InputStopRequest>(r);

  std::string name = "Biryulyovo Zapadnoye";
  std::unordered_map<std::string, int> stopToLength = {
    {"Rossoshanskaya ulitsa", 7500},
    {"Biryusinka", 1800},
    {"Universam", 2400},
  };
  double longitude = 37.6517;
  double latitude = 55.574371;

  auto expectedRequest = std::make_shared<InputStopRequest>();
  expectedRequest->SetName(name);
  expectedRequest->SetStopToLength(stopToLength);
  expectedRequest->SetLongitude(longitude);
  expectedRequest->SetLatitude(latitude);

  ASSERT(IsEqual(request, expectedRequest));
}

void Json::Tests::JsonRequestStreamParserDefaultTest()
{
  stringstream ss;
  ss << "{\n";
  ss << "\"base_requests\": [\n";

  ss << "{\n";
  ss << "\"type\": \"Stop\"\n,";
  ss << "\"name\" : \"Biryulyovo Zapadnoye\"\n,";
  ss << "\"road_distances\": {\n";
  ss << "\"Rossoshanskaya ulitsa\": 7500,\n";
  ss << "\"Biryusinka\" : 1800,\n";
  ss << "\"Universam\" : 2400\n";
  ss << "},\n";
  ss << "\"longitude\" : 37.6517,\n";
  ss << "\"latitude\" : 55.574371\n";
  ss << "},\n";

  ss << "{\n";
  ss << "\"type\": \"Bus\"\n,";
  ss << "\"name\" : \"Biryulyovo Zapadnoye\"\n,";
  ss << "\"stops\": [\n";
  ss << "\"Biryulyovo Zapadnoye\",\n";
  ss << "\"Biryusinka\",\n";
  ss << "\"Universam\",\n";
  ss << "\"Biryulyovo Tovarnaya\",\n";
  ss << "\"Biryulyovo Passazhirskaya\",\n";
  ss << "\"Biryulyovo Zapadnoye\"\n";
  ss << "],\n";
  ss << "\"is_roundtrip\": true\n";
  ss << "}\n";

  ss << "],\n";
  ss << "\"stat_requests\": [\n";

  ss << "{\n";
  ss << "\"type\": \"Bus\"\n,";
  ss << "\"name\" : \"Biryulyovo Zapadnoye\"\n,";
  ss << "\"id\" : 1042838872\n";
  ss << "},\n";

  ss << "{\n";
  ss << "\"type\": \"Stop\"\n,";
  ss << "\"name\" : \"Biryulyovo Zapadnoye\"\n,";
  ss << "\"id\" : 1042838872\n";
  ss << "}";

  ss << "]\n";
  ss << "}";

  auto streamParser = std::make_shared<RequestStreamParser>();

  auto inputBusRequestParser = std::make_shared<InputBusRequestParser>();
  streamParser->RegisterInputRequestsParser(inputBusRequestParser);
  auto inputStopRequestParser = std::make_shared<InputStopRequestParser>();
  streamParser->RegisterInputRequestsParser(inputStopRequestParser);
  auto outputBusRequestParser = std::make_shared<OutputBusRequestParser>();
  streamParser->RegisterOutputRequestsParser(outputBusRequestParser);
  auto outputStopRequestParser = std::make_shared<OutputStopRequestParser>();
  streamParser->RegisterOutputRequestsParser(outputStopRequestParser);
  streamParser->SetRequestStream(ss);

  std::vector<IRequestShp> requests;
  while (streamParser->HasRequest())
  {
    auto request = streamParser->GetNextRequest();
    if(request)
      requests.push_back(std::move(request));
  }

  auto expectedInput1 = std::make_shared<InputStopRequest>();
  {
    std::string name = "Biryulyovo Zapadnoye";
    std::unordered_map<std::string, int> stopToLength = {
      {"Rossoshanskaya ulitsa", 7500},
      {"Biryusinka", 1800},
      {"Universam", 2400},
    };
    double longitude = 37.6517;
    double latitude = 55.574371;

    expectedInput1->SetName(name);
    expectedInput1->SetStopToLength(stopToLength);
    expectedInput1->SetLongitude(longitude);
    expectedInput1->SetLatitude(latitude);
  }

  auto expectedInput2 = std::make_shared<InputBusRequest>();
  {
    std::string name = "Biryulyovo Zapadnoye";
    StringVec stops = {
      "Biryulyovo Zapadnoye",
      "Biryusinka",
      "Universam",
      "Biryulyovo Tovarnaya",
      "Biryulyovo Passazhirskaya",
      "Biryulyovo Zapadnoye",
    };
    Route::Type busType = Route::Circular;

    expectedInput2->SetName(name);
    expectedInput2->SetStops(stops);
    expectedInput2->SetBusType(busType);
  }


  auto expectedOutput1 = std::make_shared<OutputBusRequest>();
  expectedOutput1->SetId(1042838872);
  expectedOutput1->SetName("Biryulyovo Zapadnoye");

  auto expectedOutput2 = std::make_shared<OutputStopRequest>();
  expectedOutput2->SetId(1042838872);
  expectedOutput2->SetName("Biryulyovo Zapadnoye");

  size_t expectedSize = 4;

  ASSERT_EQUAL(requests.size(), expectedSize);

  {
    auto request = std::dynamic_pointer_cast<InputStopRequest>(requests[0]);
    ASSERT(IsEqual(request, expectedInput1));
  }


  {
    auto request = std::dynamic_pointer_cast<InputBusRequest>(requests[1]);
    ASSERT(IsEqual(request, expectedInput2));
  }

  {
    auto request = std::dynamic_pointer_cast<OutputBusRequest>(requests[2]);
    ASSERT(IsEqual(request, expectedOutput1));
  }

  {
    auto request = std::dynamic_pointer_cast<OutputStopRequest>(requests[3]);
    ASSERT(IsEqual(request, expectedOutput2));
  }
}
