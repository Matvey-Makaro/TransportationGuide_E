#pragma once

#include <memory>
#include <iostream>

enum class RequestType
{
	InputBus,
	InputStop,
	OutputBus,
	OutputStop,
	RoutingSettings,
	FindRoute
};
inline std::ostream& operator<<(std::ostream& out, RequestType requestType)
{
	out << static_cast<int>(requestType);
	return out;
}


class IRequest
{
public:
	virtual ~IRequest() = default;
	virtual RequestType GetType() const = 0;
};
using IRequestShp = std::shared_ptr<IRequest>;