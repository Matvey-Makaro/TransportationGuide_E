#pragma once

#include "ISpecificRequestExecutor.h"

class OutputStopRequest;
class Database;
using DatabaseShp = std::shared_ptr<Database>;

class OutputStopRequestExecutor : public ISpecificRequestExecutor
{
public:
  OutputStopRequestExecutor(DatabaseShp db);

  RequestType GetRequestType() const override;
  IResponseShp Execute(const IRequest* request) override;

private:
  const OutputStopRequest* ToOutputStopRequest(const IRequest* request) const;

private:
  DatabaseShp _db;
};

