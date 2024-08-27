#pragma once

#include <iostream>
#include <vector>
#include "IRequestStreamHandlerBuilder.h"

namespace Line
{
  class IRequestParser;
  using IRequestParserShp = std::shared_ptr<IRequestParser>;
  class IResponseFormatter;
  using IResponseFormatterShp = std::shared_ptr<IResponseFormatter>;
}

class ISpecificRequestExecutor;
using ISpecificRequestExecutorShp = std::shared_ptr<ISpecificRequestExecutor>;
class Database;
using DatabaseShp = std::shared_ptr<Database>;


class LineRequestStreamHandlerBuilder : public IRequestStreamHandlerBuilder
{
public:
  LineRequestStreamHandlerBuilder(std::istream& in,
    std::ostream& out,
    DatabaseShp db);
  IRequestStreamHandlerShp Build() override;

protected:
  IRequestStreamParserShp BuildRequestStreamParser() override;
  IRequestExecutorShp BuildRequestExecutor() override;
  IResponseStreamFormatterShp BuildResponseStreamFormatter() override;

  std::vector<Line::IRequestParserShp> BuildLineInputRequestParsers();
  std::vector<Line::IRequestParserShp> BuildLineOutputRequestParsers();

  std::vector<ISpecificRequestExecutorShp> BuildSpecificRequestExecutors();

  std::vector<Line::IResponseFormatterShp> BuildSpecificResponseFormatters();

protected:
  std::istream& _in;
  std::ostream& _out;
  DatabaseShp _db;
};
using LineRequestStreamHandlerBuilderShp = std::shared_ptr<LineRequestStreamHandlerBuilder>;
