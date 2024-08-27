#pragma once
#include "ISpecificRequestExecutor.h"

class RoutingSettingsRequest;
class Database;
using DatabaseShp = std::shared_ptr<Database>;

class RoutingSettingsRequestExecutor : public ISpecificRequestExecutor
{
public:
  RoutingSettingsRequestExecutor(DatabaseShp db);
  RequestType GetRequestType() const override;
  IResponseShp Execute(const IRequest* request) override;

private:
  const RoutingSettingsRequest* ToRoutingSettingsRequest(const IRequest* request) const;

private:
  DatabaseShp _db;
};
using RoutingSettingsRequestExecutorShp = std::shared_ptr<RoutingSettingsRequestExecutor>;
