#include <cassert>
#include "Utiils.h"
#include "BaseCommand.h"

using namespace std;

BaseCommand::BaseCommand() :
  _commandStr(nullptr),
  _result()
{}

bool BaseCommand::Do(const std::string& command)
{
  ClearPrevResults();
  _commandStr = &command;
  assert(GetCommand() == GetName());
  return true;
}

std::string BaseCommand::GetResult() const
{
  return _result.str();
}

void BaseCommand::ClearPrevResults()
{
  _commandStr = nullptr;
  _result = stringstream();
}

std::string_view BaseCommand::GetCommand() const
{
  std::string_view commandStrView = *_commandStr;
  auto [command, _] = SplitTwo(commandStrView);
  return command;
}
