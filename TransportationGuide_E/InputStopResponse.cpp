#include "InputStopResponse.h"

InputStopResponse::InputStopResponse() : AbstractResponse(RequestType::InputStop)
{
}

bool operator==(const InputStopResponse& lhs, const InputStopResponse& rhs)
{
  return true;
}

bool operator!=(const InputStopResponse& lhs, const InputStopResponse& rhs)
{
  return !(lhs == rhs);
}
