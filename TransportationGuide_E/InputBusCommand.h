#pragma once

#include <vector>
#include <string>
#include <memory>
#include "Route.h"
#include "BaseCommandWithName.h"

using StringVec = std::vector<std::string>;

class Database;
using DatabaseShp = std::shared_ptr<Database>;

class InputBusCommand : public BaseCommandWithName
{
public:
  InputBusCommand(DatabaseShp db);
  virtual ~InputBusCommand() = default;

  const std::string& GetName() const override;
  bool Do(const std::string & command) override;

protected:
  Route::Type GetRouteType() const;
  StringVec GetStops() const;

protected:
  static const std::string Name;

  DatabaseShp _db;
};

