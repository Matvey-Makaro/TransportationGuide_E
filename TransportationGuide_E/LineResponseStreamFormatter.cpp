#include "LineResponseStreamFormatter.h"

using namespace Line;

void Line::LineResponseStreamFormatter::Start(std::ostream& out)
{
  _out = &out;
}

void Line::LineResponseStreamFormatter::Format(const IResponse& response)
{
  auto it = _formatters.find(response.GetType());
  if (it == _formatters.end())
    return;
  auto& formatter = it->second;
  WriteToStream(formatter->Format(&response));
}

void Line::LineResponseStreamFormatter::Finish()
{
  // no actions
}

void Line::LineResponseStreamFormatter::RegisterResponseFormatter(const IResponseFormatterShp& formatter)
{
  if (formatter == nullptr)
    return;
  _formatters[formatter->GetType()] = formatter;
}

void Line::LineResponseStreamFormatter::WriteToStream(const std::string& str)
{
  (*_out) << str << '\n';
}
