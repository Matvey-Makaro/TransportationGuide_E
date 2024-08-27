#pragma once

#include <string>

namespace Json
{
  class Node;

  std::string GetStringByName(const Node& node, const std::string& name);
  double GetDoubleByName(const Node& node, const std::string& name);
  int GetIntByName(const Node& node, const std::string& name);
  bool GetBoolByName(const Node& node, const std::string& name);
}

