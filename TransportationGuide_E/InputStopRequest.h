#pragma once

#include <unordered_map>
#include <string>
#include "IRequest.h"

class InputStopRequest : public IRequest
{
public:
	InputStopRequest();
	virtual ~InputStopRequest() = default;

	RequestType GetType() const override;

	const std::string& GetName() const;
	void SetName(std::string name);

	double GetLatitude() const;
	void SetLatitude(double latitude);

	double GetLongitude() const;
	void SetLongitude(double longitude);

	const std::unordered_map<std::string, int>& GetStopToLength() const;
	void SetStopToLength(std::unordered_map<std::string, int> stopToLength);
	void AddLengthToStop(std::string stop, int length);

private:
	std::string _name;
	double _latitude;
	double _longitude;
	std::unordered_map<std::string, int> _stopToLength;
};
using InputStopRequestShp = std::shared_ptr<InputStopRequest>;

bool operator==(const InputStopRequest& lhs, const InputStopRequest& rhs);
bool operator!=(const InputStopRequest& lhs, const InputStopRequest& rhs);