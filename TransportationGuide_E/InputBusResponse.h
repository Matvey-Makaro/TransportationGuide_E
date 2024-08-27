#pragma once
#include "AbstractResponse.h"

class InputBusResponse : public AbstractResponse
{
public:
  InputBusResponse();

};
using InputBusResponseShp = std::shared_ptr< InputBusResponse>;

bool operator==(const InputBusResponse& lhs, const InputBusResponse& rhs);
bool operator!=(const InputBusResponse& lhs, const InputBusResponse& rhs);
