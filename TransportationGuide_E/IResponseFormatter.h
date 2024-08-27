#pragma once

#include <memory>
#include <string>
#include "IRequest.h"
#include "IResponse.h"

namespace Line
{
  class IResponseFormatter
  {
  public:
    virtual ~IResponseFormatter() = default;

    virtual RequestType GetType() = 0;
    virtual std::string Format(const IResponse* response) = 0;
  };
  using IResponseFormatterShp = std::shared_ptr<IResponseFormatter>;
}

