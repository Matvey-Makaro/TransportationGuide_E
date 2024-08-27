#include "Database.h"
#include "OutputStopCommand.h"

const std::string OutputStopCommand::Name = "Stop";

OutputStopCommand::OutputStopCommand(DatabaseShp db) :
	_db(std::move(db))
{}

const std::string& OutputStopCommand::GetName() const
{
	return Name;
}

bool OutputStopCommand::Do(const std::string& command)
{
	BaseCommandWithName::Do(command);

	_stopName = GetArgName();
	auto stop = _db->GetStop(_stopName);
	if (!stop)
	{
		_result << "Stop " << _stopName << ": not found";
		return true;
	}

	auto routes = _db->GetRoutesByStop(_stopName);
	if (routes.empty())
	{
		_result << "Stop " << _stopName << ": no buses";
		return true;
	}

	FormResult(routes);

	return true;
}

void OutputStopCommand::FormResult(const std::vector<RouteShp>& routes)
{
	std::set<std::string> sortedRoutes;
	for (const auto& r : routes)
		sortedRoutes.insert(r->GetName());

	_result << "Stop " << _stopName << ": buses";
	for (const auto& rName : sortedRoutes)
		_result << ' ' << rName;
}
