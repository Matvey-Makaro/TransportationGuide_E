#include <iostream>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include "Tests/test_runner.h"
#include "CmpUtils.h"
#include "json.h"
#include "JsonTests.h"

using namespace std;

void ParseIntTest()
{
  using namespace Json;
  stringstream ss;
  int integer = 42;
  ss << integer;

  Document doc = Load(ss);
  auto root = doc.GetRoot();


  ASSERT(root.IsInt());
  ASSERT_EQUAL(root.AsInt(), integer);
}

void ParseDoubleTest()
{
  using namespace Json;
  stringstream ss;
  double d = 42.42;
  ss << d;

  Document doc = Load(ss);
  auto root = doc.GetRoot();


  ASSERT(root.IsDouble());
  ASSERT(IsEqual(root.AsDouble(), d));
}

void ParseNegativeDoubleTest()
{
  using namespace Json;
  stringstream ss;
  double d = -42.42;
  ss << d;

  Document doc = Load(ss);
  auto root = doc.GetRoot();


  ASSERT(root.IsDouble());
  ASSERT(IsEqual(root.AsDouble(), d));
}

void ParseStringTest()
{
  using namespace Json;
  stringstream ss;
  string str = "Hello world!";
  ss << '\"' << str << '\"';

  Document doc = Load(ss);
  auto root = doc.GetRoot();


  ASSERT(root.IsString());
  ASSERT_EQUAL(root.AsString(), str);
}

void ParseArrayTest()
{
  using namespace Json;
  stringstream ss;
  vector<int> array = { 1, 2, 3, 4, 5, 6};

  ss << " [ ";
  for (size_t i = 0; i + 1 < array.size(); i++)
  {
    ss << " " << array[i] << " , ";
  }
  ss << "  " << array.back();
  ss << "  ] ";

  Document doc = Load(ss);
  auto root = doc.GetRoot();


  ASSERT(root.IsArray());
  auto nodeArray = root.AsArray();
  vector<int> resultArray;
  for (const auto& node : nodeArray)
  {
    ASSERT(node.IsInt());
    resultArray.push_back(node.AsInt());
  }
  ASSERT(IsEqual(resultArray, array));
}

void ParseDictTest()
{
  using namespace Json;
  std::unordered_map<std::string, int> dict = {
    {"one", 1},
    {"two" , 2},
    {"three" , 3},
  };

  stringstream ss;
  ss << " { ";
  int counter = 0;
  for (const auto& [key, value] : dict)
  {
    ss << std::quoted(key) << " : " << value;
    counter++;
    bool isLastElement = counter >= dict.size();
    if (!isLastElement)
      ss << " , ";
  } 
  ss << " } ";

  Document doc = Load(ss);
  auto root = doc.GetRoot();

  ASSERT(root.IsMap());
  auto rootMap = root.AsMap();
  ASSERT_EQUAL(rootMap.size(), dict.size());

  for (const auto& [key, value] : rootMap)
  {
    ASSERT(dict.count(key));
    ASSERT(value.IsInt());
    ASSERT_EQUAL(value.AsInt(), dict.at(key));
  }
}

void ParseTrueBoolTest()
{
  using namespace Json;
  stringstream ss;
  ss << "true";

  Document doc = Load(ss);
  auto root = doc.GetRoot();

  ASSERT(root.IsBool());
  ASSERT_EQUAL(root.AsBool(), true);
}

void ParseFalseBoolTest()
{
  using namespace Json;
  stringstream ss;
  ss << "false";

  Document doc = Load(ss);
  auto root = doc.GetRoot();

  ASSERT(root.IsBool());
  ASSERT_EQUAL(root.AsBool(), false);
}

void ToJsonIntTest()
{
  using namespace Json;
  int val = 42;
  Node node(val);
  Document doc(node);

  std::string expectedStr = "42";
  auto jsonStr = doc.ToJson();
  ASSERT_EQUAL(jsonStr, expectedStr)
}

void ToJsonDoubleTest()
{
  using namespace Json;
  double val = 42.42;
  Node node(val);
  Document doc(node);

  auto jsonStr = doc.ToJson();
  double jsonVal = stod(jsonStr);
  ASSERT(IsEqual(jsonVal, val));
}

void ToJsonNegativeDoubleTest()
{
  using namespace Json;
  double val = -42.42;
  Node node(val);
  Document doc(node);

  auto jsonStr = doc.ToJson();
  double jsonVal = stod(jsonStr);
  ASSERT(IsEqual(jsonVal, val));
}

void ToJsonStringTest()
{
  using namespace Json;
  string str = "Hello world!";
  Node node(str);
  Document doc(node);

  std::string expectedStr = "\"" + str + "\"";
  auto jsonStr = doc.ToJson();
  
}

void ToJsonArrayTest()
{
  using namespace Json;
  vector<int> arr = { 1, 2, 3 };
  std::vector<Node> nodes;
  for (auto i : arr)
  {
    nodes.emplace_back(i);
  }
  Node root(nodes);
  Document doc(root);
  string jsonStr = doc.ToJson();

  stringstream ss;
  ss << "[\n";
  for (size_t i = 0; i + 1 < arr.size(); i++)
  {
    ss << arr[i] << ",\n";
  }
  ss << arr.back() << '\n';
  ss << "]";

  string expectedStr = ss.str();
  ASSERT_EQUAL(jsonStr, expectedStr);
}

void ToJsonDictTest()
{
  using namespace Json;
  std::map<std::string, int> dict = {
    {"one", 1},
    {"two" , 2},
    {"three" , 3},
  };

  std::map<std::string, Node> nodes;
  for (const auto& [key, value] : dict)
  {
    nodes[key] = Node(value);
  }
  Node root(nodes);
  Document doc(root);
  string jsonStr = doc.ToJson();

  stringstream ss;
  ss << "{\n";
  int counter = 0;
  for (const auto& [key, value] : dict)
  {
    ss << std::quoted(key) << ": " << value;
    counter++;
    bool isLastElement = counter >= dict.size();
    if (!isLastElement)
      ss << ",\n";
    else ss << '\n';
  }
  ss << "}";

  string expectedStr = ss.str();
  ASSERT_EQUAL(jsonStr, expectedStr);
}

void ToJsonTrueBoolTest()
{
  using namespace Json;
  Node node(true);
  Document doc(node);

  std::string expectedStr = "true";
  auto jsonStr = doc.ToJson();
  ASSERT_EQUAL(jsonStr, expectedStr)
}

void ToJsonFalseBoolTest()
{
  using namespace Json;
  Node node(false);
  Document doc(node);

  std::string expectedStr = "false";
  auto jsonStr = doc.ToJson();
  ASSERT_EQUAL(jsonStr, expectedStr)
}

