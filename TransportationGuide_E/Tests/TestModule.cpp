#include "Tests/test_runner.h"
#include "Tests/GeoPointTests.h"
#include "Tests/InputStopCommandTests.h"
#include "Tests/InputBusCommandTests.h"
#include "Tests/OutputBusCommandTests.h"
#include "Tests/OutputStopCommandTests.h"
#include "Tests/RequestHandlerTests.h"
#include "Tests/LineInputBusRequestParserTests.h"
#include "Tests/LineInputStopRequestParserTests.h"
#include "Tests/LineOutputBusRequestParserTests.h"
#include "Tests/LineOutputStopRequestParserTests.h"
#include "Tests/LineRequestStreamParserTests.h"

#include "Tests/OutputBusRequestExecutorTests.h"
#include "Tests/OutputStopRequestExecutorTests.h"
#include "Tests/InputBusRequestExecutorTests.h"
#include "Tests/InputStopRequestExecutorTests.h"

#include "Tests/JsonTests.h"

#include "JsonRequestParsersTests.h"
#include "Tests/JsonResponseFormattersTests.h"

#include "Tests/PathSearcherTests.h"

#include "Tests/TestModule.h"

namespace
{
  void RunGeoPointTests(const TestRunner& tr)
  {
    RUN_TEST(tr, CalcDistanceSimpleTest);;
  }

  void RunInputStopCommandTests(const TestRunner& tr)
  {
    RUN_TEST(tr, InputStopCommandNameTest);
    RUN_TEST(tr, InputStopCommandStandardTest);
    RUN_TEST(tr, InputStopCommandLongStopNameTest);
    RUN_TEST(tr, InputStopCommandTwoDoTest);
    RUN_TEST(tr, InputStopCommandRoadLengthTest);
  }

  void RunInputBusCommandTests(const TestRunner& tr)
  {
    RUN_TEST(tr, InputBusCommandNameTest);
    RUN_TEST(tr, InputBusCommandCommonRouteTest);
    RUN_TEST(tr, InputBusCommandCircularRouteTest);
  }

  void RunOutputBusCommandTests(const TestRunner& tr)
  {
    RUN_TEST(tr, OutputBusCommandNameTest);
    RUN_TEST(tr, OutputBusCommandDefaultTest);
    RUN_TEST(tr, OutputBusCommandNotFoundTest);
  }

  void RunOutputStopCommandTests(const TestRunner& tr)
  {
      RUN_TEST(tr, OutputStopCommandNameTest);
      RUN_TEST(tr, OutputStopCommandDefaultTest);
      RUN_TEST(tr, OutputStopCommandNoBussesTest);
      RUN_TEST(tr, OutputStopCommandNotFoundTest);
  }

  void RunRequestHandlerTests(const TestRunner& tr)
  {
    //RUN_TEST(tr, RequestHandlerTest1);
    //RUN_TEST(tr, RequestHandlerTest2);
    RUN_TEST(tr, RequestHandlerTest3);
  }

  void RunLineInputStopRequestParserTests(const TestRunner& tr)
  {
    using namespace Line::Tests;
    RUN_TEST(tr, InputStopRequestParserNameTest);
    RUN_TEST(tr, InputStopRequestParserStandardTest);
    RUN_TEST(tr, InputStopRequestParserLongStopNameTest);
    RUN_TEST(tr, InputStopRequestParserRoadLengthTest);
  }

  void RunLineInputBusRequestParserTests(const TestRunner& tr)
  {
    using namespace Line::Tests;
    RUN_TEST(tr, InputBusRequestParserNameTest);
    RUN_TEST(tr, InputBusRequestParserCommonRouteTest);
    RUN_TEST(tr, InputBusRequestParserCircularRouteTest);
  }

  void RunLineOutputBusRequestParserTests(const TestRunner& tr)
  {
    using namespace Line::Tests;
    RUN_TEST(tr, OutputBusRequestParserNameTest);
    RUN_TEST(tr, OutputBusRequestParserDefaultTest);
  }

  void RunLineOutputStopRequestParserTests(const TestRunner& tr)
  {
    using namespace Line::Tests;
    RUN_TEST(tr, OutputStopRequestParserNameTest);
    RUN_TEST(tr, OutputStopRequestParserDefaultTest);
  }

  void RunLineRequestStreamParserTests(const TestRunner& tr)
  {
    using namespace Line::Tests;
    RUN_TEST(tr, NoRegParsersRequestStreamParserTest);
    RUN_TEST(tr, StreamRequestStreamParserTest2);
    
    RUN_TEST(tr, RequestStreamParserTest1);
  }

  void RunOutputBusRequestExecutorTests(const TestRunner& tr)
  {
    RUN_TEST(tr, OutputBusRequestExecutorTypeTest);
    RUN_TEST(tr, OutputBusRequestExecutorDefaultTest);
    RUN_TEST(tr, OutputBusRequestExecutorNotFoundTest);
  }

  void RunOutputStopRequestExecutorTests(const TestRunner& tr)
  {
    RUN_TEST(tr, OutputStopRequestExecutorTypeTest);
    RUN_TEST(tr, OutputStopRequestExecutordDefaultTest);
    RUN_TEST(tr, OutputStopRequestExecutorNoBussesTest);
    RUN_TEST(tr, OutputStopRequestExecutorNotFoundTest);
  }

  
  void RunInputBusRequestExecutorTests(const TestRunner& tr)
  {
    RUN_TEST(tr, InputBusRequestExecutorTypeTest);
    RUN_TEST(tr, InputBusRequestExecutorCommonRouteTest);
    RUN_TEST(tr, InputBusRequestExecutorCircularRouteTest);
  }

  void RunStopRequestExecutorTests(const TestRunner& tr)
  {
    RUN_TEST(tr, InputStopRequestExecutorTypeTest);
    RUN_TEST(tr, InputStopRequestExecutorStandardTest);
    RUN_TEST(tr, InputStopRequestExecutorLongStopNameTest);
    RUN_TEST(tr, InputStopRequestExecutorRoadLengthTest);
  }

  void RunJsonTests(const TestRunner& tr)
  {
    RUN_TEST(tr, ParseIntTest);
    RUN_TEST(tr, ParseDoubleTest);
    RUN_TEST(tr, ParseNegativeDoubleTest);
    RUN_TEST(tr, ParseStringTest);
    RUN_TEST(tr, ParseArrayTest);
    RUN_TEST(tr, ParseDictTest);
    //RUN_TEST(tr, DefaultParseTest);
    RUN_TEST(tr, ParseTrueBoolTest);
    RUN_TEST(tr, ParseFalseBoolTest);

    RUN_TEST(tr, ToJsonIntTest);
    RUN_TEST(tr, ToJsonDoubleTest);
    RUN_TEST(tr, ToJsonNegativeDoubleTest);
    RUN_TEST(tr, ToJsonStringTest);
    RUN_TEST(tr, ToJsonArrayTest);
    RUN_TEST(tr, ToJsonDictTest);
    RUN_TEST(tr, ToJsonTrueBoolTest);
    RUN_TEST(tr, ToJsonFalseBoolTest);
  }

  void RunJsonRequestParsersTests(const TestRunner& tr)
  {
    using namespace Json::Tests;
    RUN_TEST(tr, OutputBusRequestParserNameTest);
    RUN_TEST(tr, OutputBusRequestParserDefaultTest);

    RUN_TEST(tr, OutputStopRequestParserNameTest);
    RUN_TEST(tr, OutputStopRequestParserDefaultTest);

    RUN_TEST(tr, InputBusRequestParserNameTest);
    RUN_TEST(tr, InputBusRequestParserDefaultTest);

    RUN_TEST(tr, InputStopRequestParserNameTest);
    RUN_TEST(tr, InputStopRequestParserDefaultTest);

    RUN_TEST(tr, JsonRequestStreamParserDefaultTest);
  }
  
  //void RunJsonResponseFormattersTests(const TestRunner& tr)
  //{
  //  using namespace Json::Tests;
  //  RUN_TEST(tr, ResponseStreamFormatterDefaultTest);
  //}
  
  void RunPathSearcherTests(const TestRunner& tr)
  {
    RUN_TEST(tr, PathSearcherEmptyGraphTest);
    RUN_TEST(tr, PathSearcherTheSameBusStopTest);
    RUN_TEST(tr, PathSearcherTest1);
    RUN_TEST(tr, PathSearcherTest2);
  }

}

void TestModule::Run()
{
  TestRunner tr;

  RunGeoPointTests(tr);
  RunInputStopCommandTests(tr);
  RunInputBusCommandTests(tr);
  RunOutputBusCommandTests(tr);
  RunOutputStopCommandTests(tr);
  RunRequestHandlerTests(tr);

  RunLineInputStopRequestParserTests(tr);
  RunLineInputBusRequestParserTests(tr);
  RunLineOutputBusRequestParserTests(tr);
  RunLineOutputStopRequestParserTests(tr);
  RunLineRequestStreamParserTests(tr);

  RunOutputBusRequestExecutorTests(tr);
  RunOutputStopRequestExecutorTests(tr);
  RunInputBusRequestExecutorTests(tr);
  RunStopRequestExecutorTests(tr);

  RunJsonTests(tr);

  RunJsonRequestParsersTests(tr);

  RunPathSearcherTests(tr);
}
