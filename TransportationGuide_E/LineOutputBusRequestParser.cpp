#include "OutputBusRequest.h"
#include "LineOutputBusRequestParser.h"

using namespace std;

const std::string& Line::OutputBusRequestParser::GetRequestName() const
{
	static string name = "Bus";
	return name;
}

IRequestShp Line::OutputBusRequestParser::Parse(const std::string& line)
{
	_line = line;
	auto request = make_shared<OutputBusRequest>();
	request->SetName(string(ParseName()));
	return request;
}
