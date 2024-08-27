#pragma once

#include <memory>
#include "IRequest.h"

class AbstractOutputRequest : public IRequest
{
public:
	AbstractOutputRequest();
	virtual ~AbstractOutputRequest() = default;

	int GetId() const;
	void SetId(int id);

protected:
	int _id;
};
using AbstractOutputRequestShp = std::shared_ptr< AbstractOutputRequest>;
