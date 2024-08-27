#pragma once

#include<string>
#include<memory>
#include "IRequest.h"

namespace Line
{
	class IRequestParser
	{
	public:
		virtual ~IRequestParser() = default;

		virtual const std::string& GetRequestName() const = 0;
		virtual IRequestShp Parse(const std::string& line) = 0;
	};
	using IRequestParserShp = std::shared_ptr<IRequestParser>;
}


