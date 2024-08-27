#pragma once

#include "IResponseFormatter.h"

class OutputBusResponse;

namespace Line
{
  class OutputBusResponseFormatter : public IResponseFormatter
  {
  public:
    OutputBusResponseFormatter() = default;

    RequestType GetType() override;
    std::string Format(const IResponse* response) override;

  private:
    std::string FormatIfRouteNotFound(const OutputBusResponse* r) const;
    std::string DefaultFormat(const OutputBusResponse* r) const;
  };
  using OutputBusResponseFormatterShp = std::shared_ptr<OutputBusResponseFormatter>;
}

