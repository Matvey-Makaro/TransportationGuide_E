#pragma once

#include <unordered_map>
#include "IRequest.h"
#include "IRequestExecutor.h"
#include "ISpecificRequestExecutor.h"

class RequestStreamExecutor : public IRequestExecutor
{
public:
  RequestStreamExecutor() = default;
  IResponseShp Execute(const IRequest* request) override;

  void RegisterExecutor(ISpecificRequestExecutorShp executor);

protected:
  std::unordered_map<RequestType, ISpecificRequestExecutorShp> _requestExecutors;
};

