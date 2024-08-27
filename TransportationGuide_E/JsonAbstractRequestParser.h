#pragma once

#include <string>
#include "IJsonRequestParser.h"

namespace Json
{
  class Node;

  class AbstractRequestParser : public IRequestParser
  {
  protected:
    std::string GetStringByName(const Node& node, const std::string& name) const;
    double GetDoubleByName(const Node& node, const std::string& name) const;
    int GetIntByName(const Node& node, const std::string& name) const;
    bool GetBoolByName(const Node& node, const std::string& name) const;
  };
  using AbstractRequestParserShp = std::shared_ptr<AbstractRequestParser>;
}


