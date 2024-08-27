#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include "Utiils.h"
#include "IRequest.h"
#include "ILineRequestParser.h"
#include "IRequestStreamParser.h"
#include "SimpleRequestStreamParser.h"

namespace Line
{
	class RequestStreamParser : public IRequestStreamParser
	{
		enum State
		{
			Idle,
			Input,
			Output,
			Finished
		};
	public:
		RequestStreamParser();
		virtual ~RequestStreamParser() = default;

		void SetRequestStream(std::istream& in) override;
		bool HasRequest() const override;
		IRequestShp GetNextRequest() override;

		void RegisterInputRequestsParser(Line::IRequestParserShp parser);
		void RegisterOutputRequestsParser(Line::IRequestParserShp parser);

	private:
		void GoToNextStage();
		void OnCurrParserNoRequests();
		void GoToInputState();
		void GoToOutputState();
		void GoToFinishState();


	private:
		State _state;
		InputStreamWrapper _in;
		
		SimpleRequestStreamParser _inputRequestStreamParser;
		SimpleRequestStreamParser _outputRequestStreamParser;

		SimpleRequestStreamParser* _currParser;
	};
	using RequestStreamParserShp = std::shared_ptr<RequestStreamParser>;

}




