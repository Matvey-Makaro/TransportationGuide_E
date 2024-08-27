#pragma once

#include "ISpecificRequestExecutor.h"

class InputBusRequest;
class Database;
using DatabaseShp = std::shared_ptr<Database>;


class InputBusRequestExecutor : public ISpecificRequestExecutor
{
public:
  InputBusRequestExecutor(DatabaseShp db);

  RequestType GetRequestType() const override;
  IResponseShp Execute(const IRequest* request) override;

private:
  const InputBusRequest* ToInputBusRequest(const IRequest* request) const;

private:
  DatabaseShp _db;
};
using InputBusRequestExecutorShp = std::shared_ptr<InputBusRequestExecutor>;
