#pragma once

#include <iostream>
#include "IRequestStreamHandler.h"
#include "IRequestStreamParser.h"
#include "IRequestExecutor.h"
#include "IResponseStreamFormatter.h"

namespace Line
{
  class LineRequestStreamHandler : public IRequestStreamHandler
  {
  public:
    LineRequestStreamHandler(std::istream& in,
      std::ostream& out,
      IRequestStreamParserShp parser,
      IRequestExecutorShp executor,
      IResponseStreamFormatterShp formatter);

    void Handle() override;

  private:
    std::istream* _in;
    std::ostream* _out;
    IRequestStreamParserShp _parser;
    IRequestExecutorShp _executor;
    IResponseStreamFormatterShp _formatter;
  };
  using LineRequestStreamHandlerShp = std::shared_ptr<LineRequestStreamHandler>;
}


