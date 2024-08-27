#pragma once

#include<string>
#include<memory>
#include "IRequest.h"

namespace Json
{
	class Node;

	class IRequestParser
	{
	public:
		virtual ~IRequestParser() = default;

		virtual const std::string& GetRequestName() const = 0;
		virtual IRequestShp Parse(const Node& node) = 0;
	};
	using IRequestParserShp = std::shared_ptr<IRequestParser>;
}