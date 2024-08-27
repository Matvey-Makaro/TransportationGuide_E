#include "CmpUtils.h"
#include "InputBusRequest.h"

InputBusRequest::InputBusRequest() :
	_name(),
	_stops(),
	_busType(Route::Common)
{
}

RequestType InputBusRequest::GetType() const
{
	return RequestType::InputBus;
}

const std::string& InputBusRequest::GetName() const
{
	return _name;
}

void InputBusRequest::SetName(std::string name)
{
	_name = std::move(name);
}

const StringVec& InputBusRequest::GetStops() const
{
	return _stops;
}

void InputBusRequest::SetStops(StringVec stops)
{
	_stops = std::move(stops);
}

Route::Type InputBusRequest::GetBusType() const
{
	return _busType;
}

void InputBusRequest::SetBusType(Route::Type type)
{
	_busType = type;
}

bool operator==(const InputBusRequest& lhs, const InputBusRequest& rhs)
{
	return IsEqual(lhs.GetName(), rhs.GetName()) &&
		IsEqual(lhs.GetStops(), rhs.GetStops()) &&
		IsEqual(lhs.GetBusType(), rhs.GetBusType());
}

bool operator!=(const InputBusRequest& lhs, const InputBusRequest& rhs)
{
	return !(lhs == rhs);
}
