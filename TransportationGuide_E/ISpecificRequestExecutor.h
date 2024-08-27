#pragma once

#include "IRequestExecutor.h"
#include "IRequest.h"

class ISpecificRequestExecutor : public IRequestExecutor
{
public:
  ~ISpecificRequestExecutor() = default;

  virtual RequestType GetRequestType() const = 0;
};
using ISpecificRequestExecutorShp = std::shared_ptr<ISpecificRequestExecutor>;
