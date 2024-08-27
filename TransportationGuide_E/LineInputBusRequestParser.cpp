#include <unordered_map>
#include <cassert>
#include "InputBusRequest.h"
#include "LineInputBusRequestParser.h"

using namespace std;

namespace
{
    const std::unordered_map<std::string, Route::Type>& GetDelimiterToRouteType()
    {
        static const std::unordered_map<std::string, Route::Type> DelimiterToRouteType = {
        {"-", Route::Type::Common},
        {">", Route::Type::Circular},
        };
        return DelimiterToRouteType;
    }

    const std::unordered_map<Route::Type, std::string>& GetRouteTypeToDelimiter()
    {
        static const std::unordered_map<Route::Type, std::string> RouteTypeToDelimiter = []()
            {
                std::unordered_map<Route::Type, std::string> result;
                for (const auto& [del, type] : GetDelimiterToRouteType())
                    result[type] = del;
                return result;
            }();
            return RouteTypeToDelimiter;
    }
}

const std::string& Line::InputBusRequestParser::GetRequestName() const
{
	static string name = "Bus";
	return name;
}

IRequestShp Line::InputBusRequestParser::Parse(const std::string& line)
{
	_line = line;
	auto request = std::make_shared<InputBusRequest>();
	request->SetName(std::string(ParseName()));
	request->SetBusType(ParseBusType());
  request->SetStops(ParseStops());
	return request;
}

Route::Type Line::InputBusRequestParser::ParseBusType() const
{
    for (const auto& [del, type] : GetDelimiterToRouteType())
    {
        if (_line.find(del) != _line.npos)
            return type;
    }
    assert(0);
    return Route::Type::Common;
}

StringVec Line::InputBusRequestParser::ParseStops() const
{
    auto type = ParseBusType();
    auto del = GetRouteTypeToDelimiter().at(type);

    StringVec stops;
    auto [_, stopsStr] = SplitTwo(_line, ":");

    while (!stopsStr.empty())
    {
        auto stopName = Strip(ReadToken(stopsStr, del));
        if (!stopName.empty())
            stops.push_back(std::string(stopName));
    }
    return stops;
}
