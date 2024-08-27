#pragma once

#include <memory>
#include <iostream>
#include <functional>
#include "IRequest.h"

class IRequestStreamParser
{
public:
	virtual ~IRequestStreamParser() = default;

	virtual void SetRequestStream(std::istream& in) = 0;
	virtual bool HasRequest() const = 0;
	virtual IRequestShp GetNextRequest() = 0;
};
using IRequestStreamParserShp = std::shared_ptr<IRequestStreamParser>;