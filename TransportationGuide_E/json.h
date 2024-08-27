#pragma once

#include <istream>
#include <map>
#include <string>
#include <variant>
#include <vector>

namespace Json {

  class Node : std::variant<std::monostate,
                            std::vector<Node>,
                            std::map<std::string, Node>,
                            int,
                            double,
                            std::string,
                            bool> {
  public:
    using variant::variant;

    bool IsEmpty() const
    {
      return std::holds_alternative<std::monostate>(*this);
    }

    bool IsNumber() const
    {
      return std::holds_alternative<int>(*this) || std::holds_alternative<double>(*this);
    }

    bool IsArray() const
    {
      return std::holds_alternative<std::vector<Node>>(*this);
    }

    const auto& AsArray() const 
    {
      return std::get<std::vector<Node>>(*this);
    }

    bool IsMap() const
    {
      return std::holds_alternative<std::map<std::string, Node>>(*this);
    }

    const auto& AsMap() const 
    {
      return std::get<std::map<std::string, Node>>(*this);
    }

    bool IsInt() const
    {
      return std::holds_alternative<int>(*this);
    }

    int AsInt() const 
    {
      if(IsDouble())
        return static_cast<int>(std::get<double>(*this));
      return std::get<int>(*this);
    }

    bool IsDouble() const
    {
      return std::holds_alternative<double>(*this);
    }

    double AsDouble() const
    {
      if (IsInt())
        return std::get<int>(*this);
      return std::get<double>(*this);
    }

    bool IsString() const
    {
      return std::holds_alternative<std::string>(*this);
    }

    const auto& AsString() const 
    {
      return std::get<std::string>(*this);
    }

    bool IsBool() const
    {
      return std::holds_alternative<bool>(*this);
    }

    const auto& AsBool() const
    {
      return std::get<bool>(*this);
    }
  };

  class Document {
  public:
    explicit Document(Node root);

    const Node& GetRoot() const;
    std::string ToJson() const;

  private:
    Node root;
  };

  Document Load(std::istream& input);
}
