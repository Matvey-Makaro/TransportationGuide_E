#pragma once

#include "IResponseFormatter.h"

namespace Line
{
  class InputStopResponseFormatter : public IResponseFormatter
  {
  public:
    RequestType GetType() override;
    std::string Format(const IResponse* response) override;
  };
  using InputStopResponseFormatterShp = std::shared_ptr<InputStopResponseFormatter>;
}


