#pragma once

#include <memory>
#include <string_view>
#include "BaseCommandWithName.h"

class Database;
using DatabaseShp = std::shared_ptr<Database>;

struct StopAndLength
{
	std::string Stop;
	int Length;
};

class InputStopCommand : public BaseCommandWithName
{
public:
  InputStopCommand(DatabaseShp db);
  virtual ~InputStopCommand() = default;

  const std::string& GetName() const override;
  bool Do(const std::string & command) override;

protected:
  double GetLatitude() const;
  double GetLongitude() const;
  std::vector<StopAndLength> GetStopsAndLengths() const;

protected:
  static const std::string Name;
  DatabaseShp _db;
};
using InputStopCommandShp = std::shared_ptr<InputStopCommand>;
