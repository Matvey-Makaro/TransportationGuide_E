#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include "IRequestStreamHandler.h"
#include "IRequestStreamParser.h"
#include "IRequestExecutor.h"
#include "IResponseStreamFormatter.h"

namespace Json
{
  class JsonRequestStreamHandler : public IRequestStreamHandler
  {
  public:
    using OnBaseRequestsHandledCb = std::function<void()>;

    JsonRequestStreamHandler(std::istream& in,
      std::ostream& out,
      IRequestStreamParserShp parser,
      IRequestExecutorShp executor,
      IResponseStreamFormatterShp formatter);

    void Handle() override;

    void AddOnBaseRequestsHandledCb(OnBaseRequestsHandledCb cb);
    void OnBaseRequestsParsed();


  private:
    void OnBaseRequestsHandled();

  private:
    std::istream* _in;
    std::ostream* _out;
    IRequestStreamParserShp _parser;
    IRequestExecutorShp _executor;
    IResponseStreamFormatterShp _formatter;

    std::vector<OnBaseRequestsHandledCb> _onBaseRequestsHandledCbs;
    bool _isBaseRequestsParsed;
  };
  using JsonRequestStreamHandlerShp = std::shared_ptr<JsonRequestStreamHandler>;
  using JsonRequestStreamHandlerWkp = std::weak_ptr<JsonRequestStreamHandler>;
}

