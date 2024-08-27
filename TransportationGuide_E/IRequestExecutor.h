#pragma once

#include <memory>

class IRequest;
class IResponse;
using IResponseShp = std::shared_ptr<IResponse>;

class IRequestExecutor
{
public:
  virtual ~IRequestExecutor() = default;

  virtual IResponseShp Execute(const IRequest* request) = 0;

};
using IRequestExecutorShp = std::shared_ptr<IRequestExecutor>;