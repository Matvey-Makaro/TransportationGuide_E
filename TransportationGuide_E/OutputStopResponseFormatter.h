#pragma once

#include "IResponseFormatter.h"

class OutputStopResponse;

namespace Line
{
  class OutputStopResponseFormatter : public IResponseFormatter
  {
  public:
    RequestType GetType() override;
    std::string Format(const IResponse* response) override;

  private:
    std::string FormatStopNotFound(const OutputStopResponse* response) const;
    std::string FormatNoBusses(const OutputStopResponse* response) const;
    std::string SuccessFormat(const OutputStopResponse* response) const;
  };
  using OutputStopResponseFormatterShp = std::shared_ptr<OutputStopResponseFormatter>;
}


