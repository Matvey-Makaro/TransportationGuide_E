#pragma once

#include <memory>
#include "BaseCommandWithName.h"

class Database;
using DatabaseShp = std::shared_ptr<Database>;

class OutputStopCommand : public BaseCommandWithName
{
public:
    OutputStopCommand(DatabaseShp db);
    virtual ~OutputStopCommand() = default;

    const std::string& GetName() const override;
    bool Do(const std::string& command) override;

protected:
    void FormResult(const std::vector<RouteShp>& routes);

protected:
    static const std::string Name;

    DatabaseShp _db;
    std::string_view _stopName;
};
using OutputStopCommandShp = std::shared_ptr<OutputStopCommand>;
