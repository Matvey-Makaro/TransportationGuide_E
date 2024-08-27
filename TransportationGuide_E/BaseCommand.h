#pragma once
#include <sstream>
#include "ICommand.h"

class BaseCommand : public ICommand
{
public:
  BaseCommand();
  virtual ~BaseCommand() = default;

  bool Do(const std::string& command) override;
  std::string GetResult() const override;

protected:
  void ClearPrevResults();
  std::string_view GetCommand() const;

protected:
  StringPtr _commandStr;
  std::stringstream _result;
};

