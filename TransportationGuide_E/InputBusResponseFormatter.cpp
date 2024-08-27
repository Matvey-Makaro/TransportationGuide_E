#include "IRequest.h"
#include "InputBusResponse.h"
#include "InputBusResponseFormatter.h"

RequestType Line::InputBusResponseFormatter::GetType()
{
  return RequestType::InputBus;
}

std::string Line::InputBusResponseFormatter::Format(const IResponse* response)
{
  return {};
}
