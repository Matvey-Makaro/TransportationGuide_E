#pragma once

#include "IResponseFormatter.h"

class InputBusResponse;

namespace Line
{
  class InputBusResponseFormatter : public IResponseFormatter
  {
  public:
    RequestType GetType() override;
    std::string Format(const IResponse* response) override;
  };
  using InputBusResponseFormatterShp = std::shared_ptr<InputBusResponseFormatter>;
}


