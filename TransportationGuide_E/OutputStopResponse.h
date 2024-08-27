#pragma once

#include <vector>
#include "AbstractResponse.h"
#include "Stop.h"
#include "Route.h"

class OutputStopResponse : public AbstractOutputResponse
{
public:
  OutputStopResponse();

  const std::string& GetStopName() const;
  void SetStopName(std::string name);

  bool IsStopExist() const;
  const StopShp& GetStop() const;
  void SetStop(StopShp stop);

  bool HasRoutes() const;
  const std::vector<RouteShp>& GetRoutes() const;
  void SetRoutes(std::vector<RouteShp> routes);

private:
  std::string _stopName;
  StopShp _stop;
  std::vector<RouteShp> _routes;
};
using OutputStopResponseShp = std::shared_ptr<OutputStopResponse>;

bool operator==(const OutputStopResponse& lhs, const OutputStopResponse& rhs);
bool operator!=(const OutputStopResponse& lhs, const OutputStopResponse& rhs);
