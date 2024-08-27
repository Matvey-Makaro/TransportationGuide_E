#pragma once

#include <memory>
#include "BaseCommandWithName.h"

class Database;
using DatabaseShp = std::shared_ptr<Database>;

class OutputBusCommand : public BaseCommandWithName
{
public:
  OutputBusCommand(DatabaseShp db);
  virtual ~OutputBusCommand() = default;

  const std::string& GetName() const override;
  bool Do(const std::string & command) override;

protected:
  void FormResultIfRouteNotExist(const std::string& routeName);
  void FormResult(const std::string& busName,
      int stopsOnRouteNum,
      int uniqueStopsNum,
      double routeLength,
      double curvature);

protected:
  static const std::string Name;

  DatabaseShp _db;
};

