#include "Utiils.h"
#include "LineAbstractRequestWithNameParser.h"

std::string_view Line::AbstractRequestWithNameParser::ParseName() const
{
	auto [command, rhs] = SplitTwo(_line);
	auto [name, _] = SplitTwo(rhs, ":");
	return Strip(name);
}
