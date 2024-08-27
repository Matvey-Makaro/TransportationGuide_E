#pragma once

#include "AbstractOutputRequest.h"

class FindRouteRequest : public AbstractOutputRequest
{
public:
	virtual ~FindRouteRequest() = default;

	RequestType GetType() const override;

	const std::string& GetFromStop() const;
	void SetFromStop(std::string name);

	const std::string& GetToStop() const;
	void SetToStop(std::string name);

private:
	std::string _fromStop;
	std::string _toStop;
};
using FindRouteRequestShp = std::shared_ptr<FindRouteRequest>;

bool operator==(const FindRouteRequest& lhs, const FindRouteRequest& rhs);
bool operator!=(const FindRouteRequest& lhs, const FindRouteRequest& rhs);
