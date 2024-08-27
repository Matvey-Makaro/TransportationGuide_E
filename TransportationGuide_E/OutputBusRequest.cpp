#include "CmpUtils.h"
#include "OutputBusRequest.h"

RequestType OutputBusRequest::GetType() const
{
	return RequestType::OutputBus;
}

const std::string& OutputBusRequest::GetName() const
{
	return _name;
}

void OutputBusRequest::SetName(std::string name)
{
	_name = std::move(name);
}

bool operator==(const OutputBusRequest& lhs, const OutputBusRequest& rhs)
{
	return IsEqual(lhs.GetId(), rhs.GetId()) &&
		IsEqual(lhs.GetName(), rhs.GetName());
}

bool operator!=(const OutputBusRequest& lhs, const OutputBusRequest& rhs)
{
	return !(lhs == rhs);
}
