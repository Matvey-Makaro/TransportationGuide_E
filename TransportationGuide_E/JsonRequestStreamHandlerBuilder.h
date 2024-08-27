#pragma once
#include "IRequestStreamHandlerBuilder.h"

#include <iostream>
#include <vector>
#include "IRequestStreamHandlerBuilder.h"

namespace Json
{
  class IRequestParser;
  using IRequestParserShp = std::shared_ptr<IRequestParser>;
  class IResponseFormatter;
  using IResponseFormatterShp = std::shared_ptr<IResponseFormatter>;
  class RequestStreamParser;
  using RequestStreamParserShp = std::shared_ptr<RequestStreamParser>;
}

class ISpecificRequestExecutor;
using ISpecificRequestExecutorShp = std::shared_ptr<ISpecificRequestExecutor>;
class Database;
using DatabaseShp = std::shared_ptr<Database>;
class PathSearcher;
using PathSearcherShp = std::shared_ptr<PathSearcher>;

namespace Json
{
  class RequestStreamHandlerBuilder : public IRequestStreamHandlerBuilder
  {
  public:
    RequestStreamHandlerBuilder(std::istream& in,
      std::ostream& out,
      DatabaseShp db);
    IRequestStreamHandlerShp Build() override;

  protected:
    IRequestStreamParserShp BuildRequestStreamParser() override;
    IRequestExecutorShp BuildRequestExecutor() override;
    IResponseStreamFormatterShp BuildResponseStreamFormatter() override;

    std::vector<Json::IRequestParserShp> BuildJsonInputRequestParsers();
    std::vector<Json::IRequestParserShp> BuildJsonOutputRequestParsers();

    std::vector<ISpecificRequestExecutorShp> BuildSpecificRequestExecutors();

    std::vector<Json::IResponseFormatterShp> BuildSpecificResponseFormatters();

    RequestStreamParserShp BuildJsonRequestStreamParser();

  protected:
    std::istream& _in;
    std::ostream& _out;
    DatabaseShp _db;
    PathSearcherShp _pathSearcher;
  };
  using JsonRequestStreamHandlerBuilderShp = std::shared_ptr<RequestStreamHandlerBuilder>;
}


