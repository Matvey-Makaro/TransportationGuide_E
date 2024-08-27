#pragma once

#include <unordered_map>
#include "IRequest.h"
#include "IResponseFormatter.h"
#include "IResponseStreamFormatter.h"

namespace Line
{
  class LineResponseStreamFormatter : public IResponseStreamFormatter
  {
  public:
    void Start(std::ostream& out) override;
    void Format(const IResponse& response) override;
    void Finish() override;

    void RegisterResponseFormatter(const IResponseFormatterShp& formatter);

  private:
    void WriteToStream(const std::string& str);

  private:
    std::ostream* _out;
    std::unordered_map<RequestType, IResponseFormatterShp> _formatters;
  };
  using LineResponseStreamFormatterShp = std::shared_ptr<LineResponseStreamFormatter>;
}

