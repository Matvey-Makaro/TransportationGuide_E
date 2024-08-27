#pragma once

#include <optional>
#include "AbstractResponse.h"
#include "Path.h"

class FindRouteResponse : public AbstractOutputResponse
{
public:
  FindRouteResponse();

  const std::optional<Path>& GetPath() const;
  void SetPath(std::optional<Path> path);

private:
  std::optional<Path> _path;

};
using FindRouteResponseShp = std::shared_ptr<FindRouteResponse>;

bool operator==(const FindRouteResponse& lhs, const FindRouteResponse& rhs);
bool operator!=(const FindRouteResponse& lhs, const FindRouteResponse& rhs);


