#pragma once
#include "ISpecificRequestExecutor.h"

class OutputBusRequest;
class Database;
using DatabaseShp = std::shared_ptr<Database>;
class PathSearcher;
using PathSearcherShp = std::shared_ptr<PathSearcher>;

class FindRouteRequestExecutor : public ISpecificRequestExecutor
{
public:
  FindRouteRequestExecutor(DatabaseShp db, PathSearcherShp pathSearcher);

  RequestType GetRequestType() const override;
  IResponseShp Execute(const IRequest* request) override;

private:
  DatabaseShp _db;
  PathSearcherShp _pathSearcher;
};
using FindRouteRequestExecutorShp = std::shared_ptr<FindRouteRequestExecutor>;


