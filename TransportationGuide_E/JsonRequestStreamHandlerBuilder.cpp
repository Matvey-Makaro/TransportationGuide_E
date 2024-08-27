
#include "Database.h"

#include "JsonRequestStreamHandler.h"
#include "JsonRequestStreamParser.h"
#include "RequestStreamExecutor.h"
#include "JsonResponseFormatters.h";

#include "JsonRequestParsers.h"

#include "OutputBusRequestExecutor.h"
#include "OutputStopRequestExecutor.h"
#include "InputBusRequestExecutor.h"
#include "InputStopRequestExecutor.h"
#include "FindRouteRequestExecutor.h"
#include "RoutingSettingsRequestExecutor.h"

#include "PathSearcher.h"

#include "JsonRequestStreamHandlerBuilder.h"

using namespace std;
using namespace Json;

RequestStreamHandlerBuilder::RequestStreamHandlerBuilder(
  std::istream& in,
  std::ostream& out,
  DatabaseShp db) :
  _in(in),
  _out(out),
  _db(std::move(db)),
  _pathSearcher(std::make_shared<PathSearcher>())
{
}

IRequestStreamHandlerShp RequestStreamHandlerBuilder::Build()
{
  auto parser = BuildJsonRequestStreamParser();

  auto requestStreamHandler = std::make_shared<JsonRequestStreamHandler>(
    _in,
    _out,
   parser,
    BuildRequestExecutor(),
    BuildResponseStreamFormatter());

  
  parser->AddOnBaseRequestsParsedCb([handler = JsonRequestStreamHandlerWkp(requestStreamHandler)]()
    {
      if (handler.expired())
        return;
      auto handlerShp = handler.lock();
      handlerShp->OnBaseRequestsParsed();
    });

  requestStreamHandler->AddOnBaseRequestsHandledCb([pathSearcher = PathSearcherWkp(_pathSearcher), db = this->_db]()
    {
      if (pathSearcher.expired())
        return;
      auto pathSearcherShp = pathSearcher.lock();
      pathSearcherShp->Initialize(*db, db->GetRoutingSettings());
    });

  return requestStreamHandler;
}

IRequestStreamParserShp RequestStreamHandlerBuilder::BuildRequestStreamParser()
{
  return BuildJsonRequestStreamParser();
}

IRequestExecutorShp RequestStreamHandlerBuilder::BuildRequestExecutor()
{
  auto executor = std::make_shared<RequestStreamExecutor>();
  auto specificExecutors = BuildSpecificRequestExecutors();
  for (auto& i : specificExecutors)
    executor->RegisterExecutor(std::move(i));
  return executor;
}

IResponseStreamFormatterShp RequestStreamHandlerBuilder::BuildResponseStreamFormatter()
{
  auto formatter = std::make_shared<ResponseStreamFormatter>();
  auto specificFormatters = BuildSpecificResponseFormatters();
  for (auto& i : specificFormatters)
    formatter->RegisterResponseFormatter(std::move(i));
  return formatter;
}

std::vector<IRequestParserShp> RequestStreamHandlerBuilder::BuildJsonInputRequestParsers()
{
  return {
  std::make_shared<InputBusRequestParser>(),
  std::make_shared<InputStopRequestParser>(),
  };
}

std::vector<IRequestParserShp> RequestStreamHandlerBuilder::BuildJsonOutputRequestParsers()
{
  return {
    std::make_shared<OutputBusRequestParser>(),
    std::make_shared<OutputStopRequestParser>(),
    std::make_shared<FindRouteRequestParser>(),
  };
}

std::vector<ISpecificRequestExecutorShp> RequestStreamHandlerBuilder::BuildSpecificRequestExecutors()
{
  return {
    std::make_shared<OutputBusRequestExecutor>(_db),
    std::make_shared<OutputStopRequestExecutor>(_db),
    std::make_shared<InputBusRequestExecutor>(_db),
    std::make_shared<InputStopRequestExecutor>(_db),
    std::make_shared<RoutingSettingsRequestExecutor>(_db),
    std::make_shared<FindRouteRequestExecutor>(_db, _pathSearcher),
  };
}

std::vector<Json::IResponseFormatterShp> RequestStreamHandlerBuilder::BuildSpecificResponseFormatters()
{
  return {
  std::make_shared<InputBusResponseFormatter>(),
  std::make_shared<InputStopResponseFormatter>(),
  std::make_shared<OutputBusResponseFormatter>(),
  std::make_shared<OutputStopResponseFormatter>(),
  std::make_shared<FindRouteResponseFormatter>()
  };
}

RequestStreamParserShp Json::RequestStreamHandlerBuilder::BuildJsonRequestStreamParser()
{
  auto parser = std::make_shared<RequestStreamParser>();
  
  parser->RegisterRoutingSettingsParser(std::make_shared<InputRoutingSettingsParser>());

  auto specificOutputParsers = BuildJsonOutputRequestParsers();
  for (auto& p : specificOutputParsers)
  {
    parser->RegisterOutputRequestsParser(std::move(p));
  }

  auto specificInputParsers = BuildJsonInputRequestParsers();
  for (auto& p : specificInputParsers)
  {
    parser->RegisterInputRequestsParser(std::move(p));
  }

  return parser;
}
