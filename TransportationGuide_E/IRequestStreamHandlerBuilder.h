#pragma once

#include <memory>
#include "IRequestStreamHandler.h"
#include "IRequestStreamParser.h"
#include "IRequestExecutor.h"
#include "IResponseStreamFormatter.h"

class IRequestStreamHandlerBuilder
{
public:
  virtual ~IRequestStreamHandlerBuilder() = default;

  virtual IRequestStreamHandlerShp Build() = 0;

protected:
  virtual IRequestStreamParserShp BuildRequestStreamParser() = 0;
  virtual IRequestExecutorShp BuildRequestExecutor() = 0;
  virtual IResponseStreamFormatterShp BuildResponseStreamFormatter() = 0;
};
using IRequestStreamHandlerBuilderShp = std::shared_ptr<IRequestStreamHandlerBuilder>;
