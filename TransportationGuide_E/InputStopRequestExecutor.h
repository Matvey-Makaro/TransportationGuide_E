#pragma once

#include "ISpecificRequestExecutor.h"

class InputStopRequest;
class Database;
using DatabaseShp = std::shared_ptr<Database>;

class InputStopRequestExecutor : public ISpecificRequestExecutor
{
public:
  InputStopRequestExecutor(DatabaseShp db);

  RequestType GetRequestType() const override;
  IResponseShp Execute(const IRequest* request) override;

private:
  const InputStopRequest* ToInputStopRequest(const IRequest* request) const;

private:
  DatabaseShp _db;
};
using InputStopRequestExecutorShp = std::shared_ptr<InputStopRequestExecutor>;
