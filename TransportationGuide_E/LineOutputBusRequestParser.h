#pragma once

#include "LineAbstractRequestWithNameParser.h"

namespace Line
{
	class OutputBusRequestParser : public AbstractRequestWithNameParser
	{
	public:
		OutputBusRequestParser() = default;

		const std::string& GetRequestName() const override;
		IRequestShp Parse(const std::string& line) override;
	};
	using OutputBusRequestParserShp = std::shared_ptr<OutputBusRequestParser>;
}



