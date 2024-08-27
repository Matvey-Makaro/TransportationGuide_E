#pragma once

#include <string>
#include "unordered_map"
#include "LineAbstractRequestWithNameParser.h"

namespace Line
{
	class InputStopRequestParser : public AbstractRequestWithNameParser
	{
	public:
		InputStopRequestParser() = default;

		const std::string& GetRequestName() const override;
		IRequestShp Parse(const std::string& line) override;

	private:
		double ParseLatitude() const;
		double ParseLongitude() const;
		std::unordered_map<std::string, int> ParseStopsToLengths() const;
	};
	using InputStopRequestParserShp = std::shared_ptr<InputStopRequestParser>;
}


