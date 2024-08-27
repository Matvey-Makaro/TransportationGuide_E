#pragma once
#include "AbstractResponse.h"

class InputStopResponse : public AbstractResponse
{
public:
  InputStopResponse();
};
using InputStopResponseShp = std::shared_ptr<InputStopResponse>;

bool operator==(const InputStopResponse& lhs, const InputStopResponse& rhs);
bool operator!=(const InputStopResponse& lhs, const InputStopResponse& rhs);
