#pragma once

#include <memory>

class IRequestStreamHandler
{
public:
  virtual ~IRequestStreamHandler() = default;

  virtual void Handle() = 0;

};
using IRequestStreamHandlerShp = std::shared_ptr<IRequestStreamHandler>;
