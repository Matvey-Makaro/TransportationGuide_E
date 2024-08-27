#include "Utiils.h"
#include "BaseCommandWithName.h"

bool BaseCommandWithName::Do(const std::string& command)
{
  return BaseCommand::Do(command);
}

std::string_view BaseCommandWithName::GetArgName() const
{
  std::string_view strView = *_commandStr;
  auto [command, rhs] = SplitTwo(strView);
  auto [name, _] = SplitTwo(rhs, ":");
  return Strip(name);
}
