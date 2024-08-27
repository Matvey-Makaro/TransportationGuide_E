#include "InputBusResponse.h"

InputBusResponse::InputBusResponse() : AbstractResponse(RequestType::InputBus)
{
}

bool operator==(const InputBusResponse& lhs, const InputBusResponse& rhs)
{
    return true;
}

bool operator!=(const InputBusResponse& lhs, const InputBusResponse& rhs)
{
  return !(lhs == rhs);
}
