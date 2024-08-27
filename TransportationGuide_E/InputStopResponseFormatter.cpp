#include "IRequest.h"
#include "InputStopResponse.h"
#include "InputStopResponseFormatter.h"

using namespace Line;

RequestType Line::InputStopResponseFormatter::GetType()
{
  return RequestType::InputStop;
}

std::string Line::InputStopResponseFormatter::Format(const IResponse* response)
{
  return std::string();
}
