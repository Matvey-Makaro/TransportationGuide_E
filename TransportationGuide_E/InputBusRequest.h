#pragma once

#include <string>
#include <vector>
#include "IRequest.h"
#include "Utiils.h"
#include "Route.h"

class InputBusRequest : public IRequest
{
public:
	InputBusRequest();
	virtual ~InputBusRequest() = default;

	RequestType GetType() const override;

	const std::string& GetName() const;
	void SetName(std::string name);

	const StringVec& GetStops() const;
	void SetStops(StringVec stops);

	Route::Type GetBusType() const;
	void SetBusType(Route::Type type);

private:
	std::string _name;
	StringVec _stops;
	Route::Type _busType;
};
using InputBusRequestShp = std::shared_ptr <InputBusRequest>;

bool operator==(const InputBusRequest& lhs, const InputBusRequest& rhs);
bool operator!=(const InputBusRequest& lhs, const InputBusRequest& rhs);