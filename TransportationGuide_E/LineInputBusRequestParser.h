#pragma once

#include "Route.h"
#include "LineAbstractRequestWithNameParser.h"

using StringVec = std::vector<std::string>;

namespace Line
{
	class InputBusRequestParser : public AbstractRequestWithNameParser
	{
	public:
		InputBusRequestParser() = default;

		const std::string& GetRequestName() const override;
		IRequestShp Parse(const std::string& line) override;

	private:
		Route::Type ParseBusType() const;
		StringVec ParseStops() const;
	};
	using InputBusRequestParserShp = std::shared_ptr<InputBusRequestParser>;
}


