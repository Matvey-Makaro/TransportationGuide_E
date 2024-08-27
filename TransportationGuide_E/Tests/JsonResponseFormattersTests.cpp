#include <string>
#include <sstream>
#include <iomanip>
#include "Utiils.h"
#include "CmpUtils.h"
#include "Tests/test_runner.h"
#include "JsonResponseFormatters.h"
#include "OutputBusResponse.h"
#include "OutputStopResponse.h"
#include "JsonResponseFormattersTests.h"

using namespace std;
using namespace Json;
using namespace Json::Tests;

void Json::Tests::ResponseStreamFormatterDefaultTest()
{
  auto streamFormatter = std::make_shared<ResponseStreamFormatter>();

  auto outputBusResponseFormatter = std::make_shared<OutputBusResponseFormatter>();
  auto outputStopResponseFormatter = std::make_shared<OutputStopResponseFormatter>();
  streamFormatter->RegisterResponseFormatter(outputBusResponseFormatter);
  streamFormatter->RegisterResponseFormatter(outputStopResponseFormatter);

  std::vector<IResponseShp> responses;

  {
    auto response1 = std::make_shared<OutputBusResponse>();
    response1->SetId(1965312327);
    response1->SetRouteName("Route1");
    response1->SetRoute(std::make_shared<Route>("Route1"));
    response1->SetStopsOnRouteNum(6);
    response1->SetUniqueStopsNum(5);
    response1->SetRoadRouteLength(5950);
    response1->SetCurvature(1.36124);
    responses.push_back(response1);
  }
  
  {
    auto response2 = std::make_shared<OutputBusResponse>();
    response2->SetId(194217464);
    responses.push_back(response2);
  }

  {
    auto response3 = std::make_shared<OutputStopResponse>();
    response3->SetId(746888088);
    responses.push_back(response3);
  }

  {
    auto response4 = std::make_shared<OutputStopResponse>();
    response4->SetId(65100610);
    response4->SetStop(std::make_shared<Stop>());
    responses.push_back(response4);
  }

  {
    auto response5 = std::make_shared<OutputStopResponse>();
    response5->SetId(1042838872);
    response5->SetStopName("Stop");
    response5->SetStop(std::make_shared<Stop>());
    std::vector<RouteShp> routes = {
      std::make_shared<Route>("256"),
      std::make_shared<Route>("828"),
    };
    response5->SetRoutes(routes);
    responses.push_back(response5);
  }

  stringstream expectedSs;
  expectedSs << "[\n";
  expectedSs << "{\n";
  expectedSs << "\"route_length\": 5950,\n";
  expectedSs << "\"request_id\" : 1965312327,\n";
  expectedSs << "\"curvature\" : 1.36124,\n";
  expectedSs << "\"stop_count\" : 6,\n";
  expectedSs << "\"unique_stop_count\" : 5\n";
  expectedSs << "},\n";
  expectedSs << "{\n";
  expectedSs << "\"request_id\": 194217464,\n";
  expectedSs << "\"error_message\" : \"not found\"\n";
  expectedSs << "},\n";
  expectedSs << "{\n";
  expectedSs << "\"request_id\": 746888088,\n";
  expectedSs << "\"error_message\" : \"not found\"\n";
  expectedSs << "},\n";
  expectedSs << "{\n";
  expectedSs << "\"buses\": [] ,\n";
  expectedSs << "\"request_id\" : 65100610\n";
  expectedSs << "},\n";
  expectedSs << "{\n";
  expectedSs << "\"buses\": [\n";
  expectedSs << "\"256\",\n";
  expectedSs << "\"828\"\n";
  expectedSs << "],\n";
  expectedSs << "\"request_id\" : 1042838872\n";
  expectedSs << "}\n";
  expectedSs << "]\n";

  string expectedJson = expectedSs.str();

  stringstream ss;
  streamFormatter->Start(ss);
  for (const auto& r : responses)
    streamFormatter->Format(*r);
  streamFormatter->Finish();

  string resultJson = ss.str();

  ASSERT_EQUAL(resultJson, expectedJson)
}
