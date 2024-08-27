#include "JsonRequestStreamHandler.h"

using namespace std;
using namespace Json;

JsonRequestStreamHandler::JsonRequestStreamHandler(
  std::istream& in,
  std::ostream& out,
  IRequestStreamParserShp parser,
  IRequestExecutorShp executor,
  IResponseStreamFormatterShp formatter) :
  _in(&in),
  _out(&out),
  _parser(std::move(parser)),
  _executor(std::move(executor)),
  _formatter(std::move(formatter)),
  _onBaseRequestsHandledCbs(),
  _isBaseRequestsParsed(false)
{}

void JsonRequestStreamHandler::Handle()
{
  _parser->SetRequestStream(*_in);
  _formatter->Start(*_out);
  while (_parser->HasRequest())
  {
    auto request = _parser->GetNextRequest();
    auto response = _executor->Execute(request.get());
    if (response)
    {
      _formatter->Format(*response);
    }

    if (_isBaseRequestsParsed)
    {
      OnBaseRequestsHandled();
      _isBaseRequestsParsed = false;
    }
  }
  _formatter->Finish();
}

void Json::JsonRequestStreamHandler::AddOnBaseRequestsHandledCb(OnBaseRequestsHandledCb cb)
{
  _onBaseRequestsHandledCbs.push_back(cb);
}

void Json::JsonRequestStreamHandler::OnBaseRequestsParsed()
{
  _isBaseRequestsParsed = true;
}

void Json::JsonRequestStreamHandler::OnBaseRequestsHandled()
{
  for (const auto& cb : _onBaseRequestsHandledCbs)
    cb();
}
