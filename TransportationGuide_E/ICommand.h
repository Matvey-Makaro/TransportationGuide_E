#pragma once

#include <string>
#include <memory>

using StringPtr = const std::string*;

class ICommand
{
public:
  ICommand() = default;
  virtual ~ICommand() = default;

  virtual const std::string& GetName() const = 0;
  virtual bool Do(const std::string& command) = 0;
  virtual std::string GetResult() const = 0;
};
using ICommandShp = std::shared_ptr< ICommand>;
