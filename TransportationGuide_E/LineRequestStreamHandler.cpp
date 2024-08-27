#include "LineRequestStreamHandler.h"

using namespace Line;

LineRequestStreamHandler::LineRequestStreamHandler(
  std::istream& in, 
  std::ostream& out, 
  IRequestStreamParserShp parser, 
  IRequestExecutorShp executor, 
  IResponseStreamFormatterShp formatter) :
  _in(&in),
  _out(&out),
  _parser(std::move(parser)),
  _executor(std::move(executor)),
  _formatter(std::move(formatter))
{}

void LineRequestStreamHandler::Handle()
{
  _parser->SetRequestStream(*_in);
  _formatter->Start(*_out);
  while (_parser->HasRequest())
  {
    auto request = _parser->GetNextRequest();
    auto response = _executor->Execute(request.get());
    _formatter->Format(*response);
  }
  _formatter->Finish();
}
