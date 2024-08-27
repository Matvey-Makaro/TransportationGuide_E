#pragma once

#include <iostream>
#include <unordered_map>
#include "ICommand.h"
#include "Stop.h"
#include "Route.h"


class RequestHandler
{
public:
  RequestHandler(std::istream& in, std::ostream& out);
  void Run();
  void RegisterInputCommand(ICommandShp cmd);
  void RegisterOutputCommand(ICommandShp cmd);

private:
  void HandleInput();
  void HandleOutput();

  int GetNumOfRequests();

private:
  std::istream& _in;
  std::ostream& _out;
  std::unordered_map<std::string_view, ICommandShp> _inputCommands;
  std::unordered_map<std::string_view, ICommandShp> _outputCommands;
};

