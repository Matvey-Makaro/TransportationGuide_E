#pragma once

#include "LineAbstractRequestWithNameParser.h"

namespace Line
{
	class OutputStopRequestParser : public AbstractRequestWithNameParser
	{
	public:
		OutputStopRequestParser() = default;

		const std::string& GetRequestName() const override;
		IRequestShp Parse(const std::string& line) override;
	};
	using OutputStopRequestParserShp = std::shared_ptr<OutputStopRequestParser>;
}


