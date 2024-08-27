#include <cassert>
#include <sstream>
#include "Database.h"
#include "Utiils.h"
#include "InputStopCommand.h"

using namespace std;

const std::string InputStopCommand::Name = "Stop";

InputStopCommand::InputStopCommand(DatabaseShp db) :
  _db(std::move(db))
{}

const std::string& InputStopCommand::GetName() const
{
  return Name;
}

bool InputStopCommand::Do(const std::string& command)
{
  BaseCommandWithName::Do(command);

  auto stop = std::make_shared<Stop>();
  stop->name = GetArgName();
  stop->location = GeoPoint{ GetLatitude(), GetLongitude() };
  _db->AddStop(stop);

  auto stopsAndLengts = GetStopsAndLengths();
  for (const auto& i : stopsAndLengts)
  {
      _db->SetRoadLength(stop->name, i.Stop, i.Length);
  }

  return true;
}

double InputStopCommand::GetLatitude() const
{
    string_view commandStrView = *_commandStr;
    auto [_, partAfterName] = SplitTwo(commandStrView, ":");

    auto latitude = ReadToken(partAfterName, ",");
    return std::stod(std::string(latitude));
}

double InputStopCommand::GetLongitude() const
{
    string_view commandStrView = *_commandStr;
    auto [_, partAfterName] = SplitTwo(commandStrView, ":");

    auto latitude = ReadToken(partAfterName, ",");
    auto longitude = ReadToken(partAfterName, ",");
    return std::stod(std::string(longitude));
}

std::vector<StopAndLength> InputStopCommand::GetStopsAndLengths() const
{
    StringVec stops;
    string_view commandStrView = *_commandStr;
    auto [_, partAfterName] = SplitTwo(commandStrView, ":");

    auto latitude = ReadToken(partAfterName, ",");
    auto longitude = ReadToken(partAfterName, ",");

    auto stopsAndLengthsStrView = partAfterName;

    std::vector<StopAndLength> stopAndLengthVec;
    while (!stopsAndLengthsStrView.empty())
    {
        auto token = ReadToken(stopsAndLengthsStrView, ",");
        stringstream ss;
        ss << token;
        int length;
        string m;
        string to;
        string stopName;
        ss >> length >> m >> to;
        getline(ss, stopName);
        assert(m == "m");
        assert(to == "to");

        if (!stopName.empty())
        {

            stopAndLengthVec.push_back({ string(Strip(stopName)), length });
        }
    }
    return stopAndLengthVec;
}
