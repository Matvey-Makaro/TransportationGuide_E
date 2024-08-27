#pragma once

#include <string>
#include "AbstractOutputRequest.h"

class OutputStopRequest : public AbstractOutputRequest
{
public:
	virtual ~OutputStopRequest() = default;

	RequestType GetType() const override;

	const std::string& GetName() const;
	void SetName(std::string name);

private:
	std::string _name;
};
using OutputStopRequestShp = std::shared_ptr<OutputStopRequest>;

bool operator==(const OutputStopRequest& lhs, const OutputStopRequest& rhs);
bool operator!=(const OutputStopRequest& lhs, const OutputStopRequest& rhs);