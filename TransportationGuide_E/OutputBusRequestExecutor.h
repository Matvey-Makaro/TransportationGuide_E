#pragma once

#include "ISpecificRequestExecutor.h"

class OutputBusRequest;
class Database;
using DatabaseShp = std::shared_ptr<Database>;

class OutputBusRequestExecutor : public ISpecificRequestExecutor
{
public:
  OutputBusRequestExecutor(DatabaseShp db);

  RequestType GetRequestType() const override;
  IResponseShp Execute(const IRequest* request) override;

private:
  const OutputBusRequest* ToOutputBusRequest(const IRequest* request) const;

private:
  DatabaseShp _db;
};
using OutputBusRequestExecutorShp = std::shared_ptr< OutputBusRequestExecutor>;
