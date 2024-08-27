#pragma once
#include "BaseCommand.h"

class BaseCommandWithName : public BaseCommand
{
public:
  BaseCommandWithName() = default;
  virtual ~BaseCommandWithName() = default;

  bool Do(const std::string& command) override;

protected:
  std::string_view GetArgName() const;

};

