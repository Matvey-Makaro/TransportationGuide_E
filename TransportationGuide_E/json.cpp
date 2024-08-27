#include <sstream>
#include <iomanip>
#include "json.h"
#include "Utiils.h"

using namespace std;

namespace
{
  bool IsSign(char ch)
  {
    return ch == '-' || ch == '+';
  }

  std::string ToJson(const std::vector<Json::Node>& arr);
  std::string ToJson(const std::map<std::string, Json::Node>& dict);
  std::string ToJson(double d);
  std::string ToJson(const std::string& str);
  std::string ToJson(const Json::Node& node);


  std::string ToJson(const std::vector<Json::Node>& arr)
  {
    stringstream ss;
    ss << "[\n";
    for (size_t i = 0; i + 1 < arr.size(); i++)
    {
      ss << ToJson(arr[i]) << ",\n";
    }
    if (!arr.empty())
    {
      ss << ToJson(arr.back()) << '\n';
    }
    ss << ']';
    return ss.str();
  }

  std::string ToJson(const std::map<std::string, Json::Node>& dict)
  {
    stringstream ss;
    ss << "{\n";
    auto it = dict.begin();
    if (it != dict.end())
    {
      for (; it != std::prev(dict.end()); it++)
      {
        ss << '\"' << it->first << "\": " << ToJson(it->second) << ",\n";
      }
      ss << '\"' << it->first << "\": " << ToJson(it->second) << "\n";
    }
    ss << "}";
    return ss.str();
  }

  std::string ToJson(int i)
  {
    return std::to_string(i);
  }

  std::string ToJson(double d)
  {
    stringstream ss;
    ss << setprecision(20) << d;
    return ss.str();
  }

  std::string ToJson(const std::string& str)
  {
    stringstream ss;
    ss << '\"' << str << '\"';
    return ss.str();
  }

  std::string ToJson(bool b)
  {
    return b ? "true" : "false";  
  }

  std::string ToJson(const Json::Node& node)
  {
    if (node.IsArray())
      return ToJson(node.AsArray());
    if (node.IsMap())
      return ToJson(node.AsMap());
    if (node.IsInt())
      return ToJson(node.AsInt());
    if (node.IsDouble())
      return ToJson(node.AsDouble());
    if (node.IsString())
      return ToJson(node.AsString());
    if (node.IsBool())
      return ToJson(node.AsBool());
    return {};
  }
}

namespace Json {

  Document::Document(Node root) : root(move(root)) {
  }

  const Node& Document::GetRoot() const {
    return root;
  }

  std::string Document::ToJson() const
  {
    return ::ToJson(root);
  }

  Node LoadNode(istream& input);

  Node LoadArray(istream& input) {
    vector<Node> result;

    for (char c; input >> c && c != ']'; ) {
      if (c != ',') {
        input.putback(c);
      }
      result.push_back(LoadNode(input));
    }

    return Node(move(result));
  }

  int LoadSignMultiplier(istream& input)
  {
    char c;
    input >> c;
    if (c == '-')
      return -1;
    
    if (c == '+')
      return 1;

    input.putback(c);
    return 1;
  }

  int64_t LoadIntegerPart(istream& input)
  {
    int64_t result = 0;
    while (isdigit(input.peek())) {
      result *= 10;
      result += input.get() - '0';
    }
    return result;
  }

  bool IsDouble(istream& input)
  {
    return input.peek() == '.';
  }

  double LoadFractionalPart(istream& input)
  {
    char dot;
    input >> dot;

    int64_t fractionPart = 0;
    double devider = 1.;
    while (isdigit(input.peek())) {
      fractionPart *= 10;
      fractionPart += input.get() - '0';
      devider *= 10;
    }
    return static_cast<double>(fractionPart) / devider;
  }

  Node LoadNumber(istream& input) {
    auto signMultiplier = LoadSignMultiplier(input);
    auto integerPart = LoadIntegerPart(input);

    if (IsDouble(input))
    {
      auto fractionPart = LoadFractionalPart(input);
      double doubleNumber = static_cast<double>(integerPart) + fractionPart;
      doubleNumber *= static_cast<double>(signMultiplier);
      return Node(doubleNumber);
    }
    else
    {
      int result = static_cast<int>(signMultiplier) * static_cast<int>(integerPart);
      return Node(result);
    }
  }

  Node LoadBool(istream& input) {
    char c;
    std::string str;
    while (isalpha(input.peek()))
    {
      str += input.get();
    }
    if (str == "true")
      return Node(true);
    else if (str == "false")
      return Node(false);
    return Node();
  }

  Node LoadString(istream& input) {
    string line;
    getline(input, line, '"');
    return Node(move(line));
  }

  Node LoadDict(istream& input) {
    map<string, Node> result;

    for (char c; input >> c && c != '}'; ) {
      if (c == ',') {
        input >> c;
      }

      string key = LoadString(input).AsString();
      if (key == "base_requests" || key == "stat_requests")
      {
        double delete_later = 0;
      }

      input >> c;
      result.emplace(move(key), LoadNode(input));
    }

    return Node(move(result));
  }

  Node LoadNode(istream& input) {
    char c;
    input >> c;

    if (c == '[') {
      return LoadArray(input);
    } else if (c == '{') {
      return LoadDict(input);
    } else if (c == '"') {
      return LoadString(input);
    } else if (isdigit(c) || IsSign(c)){
      input.putback(c);
      return LoadNumber(input);
    }
    else {
      input.putback(c);
      return LoadBool(input);
    }
  }

  Document Load(istream& input) {
    return Document{LoadNode(input)};
  }

}
