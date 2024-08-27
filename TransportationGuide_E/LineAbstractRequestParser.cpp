#include "LineAbstractRequestParser.h"

Line::AbstractRequestParser::AbstractRequestParser()
{}

const std::string_view Line::AbstractRequestParser::GetLine() const
{
    return _line;
}
