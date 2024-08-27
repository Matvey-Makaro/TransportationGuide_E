#include "CmpUtils.h"
#include "OutputStopRequest.h"

RequestType OutputStopRequest::GetType() const
{
    return RequestType::OutputStop;
}

const std::string& OutputStopRequest::GetName() const
{
    return _name;
}

void OutputStopRequest::SetName(std::string name)
{
    _name = std::move(name);
}

bool operator==(const OutputStopRequest& lhs, const OutputStopRequest& rhs)
{
  return IsEqual(lhs.GetId(), rhs.GetId()) &&
    IsEqual(lhs.GetName(), rhs.GetName());
}

bool operator!=(const OutputStopRequest& lhs, const OutputStopRequest& rhs)
{
  return !(lhs == rhs);
}
