#pragma once

#include <string>
#include "AbstractOutputRequest.h"

class OutputBusRequest : public AbstractOutputRequest
{
public:
	virtual ~OutputBusRequest() = default;

	RequestType GetType() const override;

	const std::string& GetName() const;
	void SetName(std::string name);

private:
	std::string _name;
};
using OutputBusRequestShp = std::shared_ptr<OutputBusRequest>;

bool operator==(const OutputBusRequest& lhs, const OutputBusRequest& rhs);
bool operator!=(const OutputBusRequest& lhs, const OutputBusRequest& rhs);