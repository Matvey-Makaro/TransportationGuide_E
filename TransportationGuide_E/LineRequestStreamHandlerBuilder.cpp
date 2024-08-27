#include "Database.h"

#include "LineRequestStreamHandler.h"
#include "LineRequestStreamParser.h"
#include "RequestStreamExecutor.h"
#include "LineResponseStreamFormatter.h"

#include "LineOutputBusRequestParser.h"
#include "LineOutputStopRequestParser.h"
#include "LineInputBusRequestParser.h"
#include "LineInputStopRequestParser.h"

#include "OutputBusRequestExecutor.h"
#include "OutputStopRequestExecutor.h"
#include "InputBusRequestExecutor.h"
#include "InputStopRequestExecutor.h"

#include "InputBusResponseFormatter.h"
#include "InputStopResponseFormatter.h"
#include "OutputBusResponseFormatter.h"
#include "OutputStopResponseFormatter.h"

#include "LineRequestStreamHandlerBuilder.h"

using namespace Line;

LineRequestStreamHandlerBuilder::LineRequestStreamHandlerBuilder(
  std::istream& in, 
  std::ostream& out,
  DatabaseShp db) :
  _in(in), 
  _out(out),
  _db(std::move(db))
{
}

IRequestStreamHandlerShp LineRequestStreamHandlerBuilder::Build()
{
  auto requestStreamHandler = std::make_shared<LineRequestStreamHandler>(
    _in,
    _out,
    BuildRequestStreamParser(),
    BuildRequestExecutor(),
    BuildResponseStreamFormatter());
  return requestStreamHandler;
}

IRequestStreamParserShp LineRequestStreamHandlerBuilder::BuildRequestStreamParser()
{
  auto parser = std::make_shared<RequestStreamParser>();
  parser->SetRequestStream(_in);

  auto specificOutputParsers = BuildLineOutputRequestParsers();
  for (auto& p : specificOutputParsers)
  {
    parser->RegisterOutputRequestsParser(std::move(p));
  }

  auto specificInputParsers = BuildLineInputRequestParsers();
  for (auto& p : specificInputParsers)
  {
    parser->RegisterInputRequestsParser(std::move(p));
  }

  return parser;
}

IRequestExecutorShp LineRequestStreamHandlerBuilder::BuildRequestExecutor()
{
  auto executor = std::make_shared<RequestStreamExecutor>();
  auto specificExecutors = BuildSpecificRequestExecutors();
  for (auto& i : specificExecutors)
    executor->RegisterExecutor(std::move(i));
  return executor;
}

IResponseStreamFormatterShp LineRequestStreamHandlerBuilder::BuildResponseStreamFormatter()
{
  auto formatter = std::make_shared<LineResponseStreamFormatter>();
  auto specificFormatters = BuildSpecificResponseFormatters();
  for (auto& i : specificFormatters)
    formatter->RegisterResponseFormatter(std::move(i));
  return formatter;
}

std::vector<IRequestParserShp> LineRequestStreamHandlerBuilder::BuildLineInputRequestParsers()
{
  return {
  std::make_shared<InputBusRequestParser>(),
  std::make_shared<InputStopRequestParser>(),
  };
}

std::vector<IRequestParserShp> LineRequestStreamHandlerBuilder::BuildLineOutputRequestParsers()
{
  return {
    std::make_shared<OutputBusRequestParser>(),
    std::make_shared<OutputStopRequestParser>(),
  };
}

std::vector<ISpecificRequestExecutorShp> LineRequestStreamHandlerBuilder::BuildSpecificRequestExecutors()
{
  return {
    std::make_shared<OutputBusRequestExecutor>(_db),
    std::make_shared<OutputStopRequestExecutor>(_db),
    std::make_shared<InputBusRequestExecutor>(_db),
    std::make_shared<InputStopRequestExecutor>(_db),
  };
}

std::vector<Line::IResponseFormatterShp> LineRequestStreamHandlerBuilder::BuildSpecificResponseFormatters()
{
  return {
  std::make_shared<InputBusResponseFormatter>(),
  std::make_shared<InputStopResponseFormatter>(),
  std::make_shared<OutputBusResponseFormatter>(),
  std::make_shared<OutputStopResponseFormatter>(),
  };
}
