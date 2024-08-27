#pragma once

#include <memory>
#include "IRequest.h"

class IResponse
{
public:
  virtual ~IResponse() = default;
  virtual RequestType GetType() const = 0;
};
using IResponseShp = std::shared_ptr<IResponse>;
