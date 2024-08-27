#include <sstream>
#include "InputStopRequest.h"
#include "LineInputStopRequestParser.h"
#include "Utiils.h"
#include "cassert"

using namespace std;
using namespace Line;

const std::string& InputStopRequestParser::GetRequestName() const
{
    static string name = "Stop";
    return name;
}

IRequestShp InputStopRequestParser::Parse(const std::string& line)
{
    _line = line;

    auto request = std::make_shared<InputStopRequest>();
    request->SetName(std::string(ParseName()));
    request->SetLatitude(ParseLatitude());
    request->SetLongitude(ParseLongitude());
    request->SetStopToLength(ParseStopsToLengths());
    return request;
}

double Line::InputStopRequestParser::ParseLatitude() const
{
    auto [_, partAfterName] = SplitTwo(_line, ":");
    auto latitude = ReadToken(partAfterName, ",");
    return std::stod(std::string(latitude));
}

double Line::InputStopRequestParser::ParseLongitude() const
{
    auto [_, partAfterName] = SplitTwo(_line, ":");

    auto latitude = ReadToken(partAfterName, ",");
    auto longitude = ReadToken(partAfterName, ",");
    return std::stod(std::string(longitude));
}

std::unordered_map<std::string, int> Line::InputStopRequestParser::ParseStopsToLengths() const
{
    StringVec stops;
    auto [_, partAfterName] = SplitTwo(_line, ":");

    auto latitude = ReadToken(partAfterName, ",");
    auto longitude = ReadToken(partAfterName, ",");

    auto stopsToLengthsStrView = partAfterName;

    unordered_map<std::string, int> stopToLength;
    while (!stopsToLengthsStrView.empty())
    {
        auto token = ReadToken(stopsToLengthsStrView, ",");
        stringstream ss;
        ss << token;
        int length;
        string m;
        string to;
        string stopName;
        ss >> length >> m >> to;
        getline(ss, stopName);
        stopName = Strip(stopName);
        assert(m == "m");
        assert(to == "to");

        if (!stopName.empty())
        {
            stopToLength[string(stopName)] = length;
        }
    }
    return stopToLength;
}
