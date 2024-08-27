#pragma once

#include <memory>
#include <iostream>
#include "IResponse.h"

class IResponseStreamFormatter
{
public:
  virtual ~IResponseStreamFormatter() = default;

  virtual void Start(std::ostream& out) = 0;
  virtual void Format(const IResponse& response) = 0;
  virtual void Finish() = 0;

};
using IResponseStreamFormatterShp = std::shared_ptr<IResponseStreamFormatter>;
