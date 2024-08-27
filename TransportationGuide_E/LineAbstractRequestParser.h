#pragma once

#include <string_view>
#include "ILineRequestParser.h"

namespace Line
{
	class AbstractRequestParser : public IRequestParser
	{
	public:
		AbstractRequestParser();
		const std::string_view GetLine() const;

	protected:
		std::string_view _line;
	};
	using AbstractRequestParserShp = std::shared_ptr<AbstractRequestParser>;
}



