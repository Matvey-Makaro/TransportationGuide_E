#include <set>
#include <sstream>
#include "IRequest.h"
#include "OutputStopResponse.h"
#include "OutputStopResponseFormatter.h"
#include "JsonResponseFormatters.h"

using namespace Line;

RequestType OutputStopResponseFormatter::GetType()
{
  return RequestType::OutputStop;
}

std::string OutputStopResponseFormatter::Format(const IResponse* response)
{
	auto r = dynamic_cast<const OutputStopResponse*>(response);
	if (r == nullptr)
		return {};

	if (!r->IsStopExist())
	{
		return FormatStopNotFound(r);
	}
	if (!r->HasRoutes())
	{
		return FormatNoBusses(r);
	}
	return SuccessFormat(r);
}


std::string OutputStopResponseFormatter::FormatStopNotFound(const OutputStopResponse* response) const
{
	return "Stop " + response->GetStopName() + ": not found";
}

std::string OutputStopResponseFormatter::FormatNoBusses(const OutputStopResponse* response) const
{
	return "Stop " + response->GetStopName() + ": no buses";
}

std::string OutputStopResponseFormatter::SuccessFormat(const OutputStopResponse* response) const
{
	std::set<std::string> sortedRoutes;
	const auto& routes = response->GetRoutes();
	for (const auto& r : routes)
		sortedRoutes.insert(r->GetName());

	std::stringstream ss;
	ss << "Stop " << response->GetStopName() << ": buses";
	for (const auto& rName : sortedRoutes)
		ss << ' ' << rName;
	return ss.str();
}
