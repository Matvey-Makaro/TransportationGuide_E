#include <cassert>
#include <string_view>
#include <optional>
#include <algorithm>
#include <iomanip>
#include "Utiils.h"
#include "RequestHandler.h"

using namespace std;



RequestHandler::RequestHandler(std::istream& in, std::ostream& out) :
  _in(in),
  _out(out)
{}

void RequestHandler::Run()
{
  HandleInput();
  HandleOutput();
}

void RequestHandler::RegisterInputCommand(ICommandShp cmd)
{
  _inputCommands[cmd->GetName()] = std::move(cmd);
}

void RequestHandler::RegisterOutputCommand(ICommandShp cmd)
{
  _outputCommands[cmd->GetName()] = std::move(cmd);
}

void RequestHandler::HandleInput()
{
  int numOfRequests = GetNumOfRequests();
  for (int i = 0; i < numOfRequests; i++)
  {
    string commandStr;
    std::getline(_in, commandStr);
    auto [commandName, _] = SplitTwo(commandStr);
    auto& command = _inputCommands.at(commandName);
    command->Do(commandStr);
  }
}

void RequestHandler::HandleOutput()
{
  int numOfRequests = GetNumOfRequests();
  for (int i = 0; i < numOfRequests; i++)
  {
    string commandStr;
    std::getline(_in, commandStr);
    auto [commandName, _] = SplitTwo(commandStr);
    auto& command = _outputCommands.at(commandName);
    command->Do(commandStr);
    auto result = command->GetResult();
    if (!result.empty())
    {
      _out << result << '\n'; // TODO: ¬озможно при последнем ответе не надо ставить '\n'
    }
  }
}

int RequestHandler::GetNumOfRequests()
{
  string str;
  getline(_in, str);
  int numOfRequests = stoi(str);
  return numOfRequests;
}
