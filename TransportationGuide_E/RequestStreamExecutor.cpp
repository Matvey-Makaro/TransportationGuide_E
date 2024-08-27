#include "RequestStreamExecutor.h"

IResponseShp RequestStreamExecutor::Execute(const IRequest* request)
{
  if (request == nullptr)
    return {};

  auto it = _requestExecutors.find(request->GetType());
  if (it == _requestExecutors.end())
    return {};

  auto& executor = it->second;
  return executor->Execute(request);
}

void RequestStreamExecutor::RegisterExecutor(ISpecificRequestExecutorShp executor)
{
  if (executor == nullptr)
    return;
  _requestExecutors[executor->GetRequestType()] = std::move(executor);
}
