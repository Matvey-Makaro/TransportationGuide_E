#include "CmpUtils.h"
#include "InputStopRequest.h"

InputStopRequest::InputStopRequest() :
	_name(),
	_latitude(0.),
	_longitude(0.),
	_stopToLength()
{}

RequestType InputStopRequest::GetType() const
{
	return RequestType::InputStop;
}

const std::string& InputStopRequest::GetName() const
{
	return _name;
}

void InputStopRequest::SetName(std::string name)
{
	_name = std::move(name);
}

double InputStopRequest::GetLatitude() const
{
	return _latitude;
}

void InputStopRequest::SetLatitude(double latitude)
{
	_latitude = latitude;
}

double InputStopRequest::GetLongitude() const
{
	return _longitude;
}

void InputStopRequest::SetLongitude(double longitude)
{
	_longitude = longitude;
}

const std::unordered_map<std::string, int>& InputStopRequest::GetStopToLength() const
{
	return _stopToLength;
}

void InputStopRequest::SetStopToLength(std::unordered_map<std::string, int> stopToLength)
{
	_stopToLength = std::move(stopToLength);
}

void InputStopRequest::AddLengthToStop(std::string stop, int length)
{
	_stopToLength[std::move(stop)] = length;
}

bool operator==(const InputStopRequest& lhs, const InputStopRequest& rhs)
{
	return IsEqual(lhs.GetName(), rhs.GetName()) &&
		IsEqual(lhs.GetLatitude(), rhs.GetLatitude()) &&
		IsEqual(lhs.GetLongitude(), rhs.GetLongitude()) &&
		IsEqual(lhs.GetStopToLength(), rhs.GetStopToLength());
}

bool operator!=(const InputStopRequest& lhs, const InputStopRequest& rhs)
{
	return !(lhs == rhs);
}
