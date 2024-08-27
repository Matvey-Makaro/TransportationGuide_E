#include "LineRequestStreamParser.h"
#include "JsonRequestStreamParser.h"

Line::RequestStreamParser::RequestStreamParser() :
	_state(Idle),
	_in(),
	_inputRequestStreamParser(),
	_outputRequestStreamParser(),
	_currParser(&_inputRequestStreamParser)
{}

void Line::RequestStreamParser::SetRequestStream(std::istream& in)
{
	_in = InputStreamWrapper(in);
	GoToNextStage();
}

bool Line::RequestStreamParser::HasRequest() const
{
	if (_state == Finished)
		return false;

	return _currParser->HasRequest();
}

IRequestShp Line::RequestStreamParser::GetNextRequest()
{
	if (!HasRequest())
		return {};

	auto request = _currParser->GetNextRequest();
	GoToNextStage();

	return request;
}

void Line::RequestStreamParser::RegisterInputRequestsParser(Line::IRequestParserShp parser)
{
	_inputRequestStreamParser.RegisterRequestsParser(parser);
}

void Line::RequestStreamParser::RegisterOutputRequestsParser(Line::IRequestParserShp parser)
{
	_outputRequestStreamParser.RegisterRequestsParser(parser);
}

void Line::RequestStreamParser::GoToNextStage()
{
	while (_state != Finished && !_currParser->HasRequest())
	{
		OnCurrParserNoRequests();
	}
}

void Line::RequestStreamParser::OnCurrParserNoRequests()
{
	switch (_state)
	{
	case Line::RequestStreamParser::Idle: GoToInputState();
		break;
	case Line::RequestStreamParser::Input: GoToOutputState();
		break;
	case Line::RequestStreamParser::Output: GoToFinishState();
	}
}

void Line::RequestStreamParser::GoToInputState()
{
	_state = Input;
	_currParser = &_inputRequestStreamParser;
	_currParser->SetRequestStream(_in.GetStream());
}

void Line::RequestStreamParser::GoToOutputState()
{
	_state = Output;
	_currParser = &_outputRequestStreamParser;
	_currParser->SetRequestStream(_in.GetStream());
}

void Line::RequestStreamParser::GoToFinishState()
{
	_state = Finished;
}
