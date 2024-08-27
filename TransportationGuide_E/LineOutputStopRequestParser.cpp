#include "OutputStopRequest.h"
#include "LineOutputStopRequestParser.h"

using namespace std;

const std::string& Line::OutputStopRequestParser::GetRequestName() const
{
	static string name = "Stop";
	return name;
}

IRequestShp Line::OutputStopRequestParser::Parse(const std::string& line)
{
	_line = line;
	auto request = std::make_shared<OutputStopRequest>();
	request->SetName(string(ParseName()));
	return request;
}
