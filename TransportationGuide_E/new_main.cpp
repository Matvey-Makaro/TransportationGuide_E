
#include <memory>
#include <vector>

template<typename T>
bool IsEqual(const T& lhs, const T& rhs)
{
  return lhs == rhs;
}

template<typename T>
bool IsEqual(const std::shared_ptr<T>& lhs, const std::shared_ptr<T>& rhs)
{
  if (!lhs && !rhs)
    return true;
  if (!lhs)
    return false;
  if (!rhs)
    return false;
  return IsEqual(*lhs, *rhs);
}

template<typename T>
bool IsEqual(const std::vector<T>& lhs, const std::vector<T>& rhs)
{
  if (lhs.size() != rhs.size())
    return false;
  const auto size = lhs.size();
  for (size_t i = 0; i < size; i++)
  {
    if (!IsEqual(lhs[i], rhs[i]))
      return false;
  }
  return true;
}

bool IsEqual(double lhs, double rhs, double eps = 0.0001);


#include <cmath>

bool IsEqual(double lhs, double rhs, double eps)
{
  return std::fabs(lhs - rhs) <= eps;
}



#include <tuple>
#include <string>
#include <string_view>
#include <optional>
#include <vector>
#include <iostream>
#include <memory>

using StringVec = std::vector<std::string>;

std::pair<std::string_view, std::optional<std::string_view>> SplitTwoStrict(std::string_view s, std::string_view delimiter = " ");
std::pair<std::string_view, std::string_view> SplitTwo(std::string_view s, std::string_view delimiter = " ");
std::string_view ReadToken(std::string_view& s, std::string_view delimiter = " ");
std::vector<std::string_view> Tokenize(const std::string& str);

std::pair<std::optional<std::string_view>, std::string_view> SplitTwoStrictFromEnd(std::string_view s, std::string_view delimiter = " ");
std::pair<std::string_view, std::string_view> SplitTwoFromEnd(std::string_view s, std::string_view delimiter = " ");
std::string_view ReadTokenFromEnd(std::string_view& s, std::string_view delimiter = " ");

std::string_view LStrip(std::string_view s);
std::string_view RStrip(std::string_view s);
std::string_view Strip(std::string_view s);

class InputStreamWrapper
{
public:
	InputStreamWrapper();
	InputStreamWrapper(std::istream& in);
	
	InputStreamWrapper(const InputStreamWrapper& other) = default;
	InputStreamWrapper(InputStreamWrapper&& other) = default;

	InputStreamWrapper& operator=(const InputStreamWrapper& other) = default;
	InputStreamWrapper& operator=(InputStreamWrapper&& other) = default;

	bool IsNull() const;

	const std::istream& GetStream() const;
	std::istream& GetStream();

private:
	std::istream* _in;
};

template<typename T>
InputStreamWrapper& operator>>(InputStreamWrapper& in, T& value)
{
	in.GetStream() >> value;
	return in;
}

constexpr double KmHToMMin(double speedKmH) 
{
	return speedKmH * 1000. / 60.;
}
#include <algorithm>

using namespace std;

pair<string_view, optional<string_view>> SplitTwoStrict(string_view s, string_view delimiter)
{
  const size_t pos = s.find(delimiter);
  if (pos == s.npos)
    return { s, nullopt };
  else return { s.substr(0, pos), s.substr(pos + delimiter.length()) };
}

pair<string_view, string_view> SplitTwo(string_view s, string_view delimiter)
{
  const auto [lhs, rhs_opt] = SplitTwoStrict(s, delimiter);
  return { lhs, rhs_opt.value_or("")};
}

string_view ReadToken(string_view& s, string_view delimiter)
{
  const auto [lhs, rhs] = SplitTwo(s, delimiter);
  s = rhs;
  return lhs;
}

vector<string_view> Tokenize(const std::string& str)
{
  vector<string_view> tokens;
  string_view strView = str;
  while (!strView.empty())
  {
    auto token = ReadToken(strView);
    if (!token.empty())
      tokens.push_back(token);
  }
  return tokens;
}

pair<optional<string_view>, string_view> SplitTwoStrictFromEnd(string_view s, string_view delimiter)
{
  const size_t pos = s.find_last_of(delimiter);
  if (pos == s.npos)
    return { nullopt, s };
  else return { s.substr(0, pos), s.substr(pos + delimiter.length()) };
}

pair<string_view, string_view> SplitTwoFromEnd(string_view s, string_view delimiter)
{
  const auto [lhs, rhs_opt] = SplitTwoStrictFromEnd(s, delimiter);
  return { lhs.value_or(""), rhs_opt };
}

string_view ReadTokenFromEnd(string_view& s, string_view delimiter)
{
  const auto [lhs, rhs] = SplitTwoFromEnd(s, delimiter);
  s = lhs;
  return rhs;
}

string_view LStrip(string_view s)
{
  auto pos = s.find_first_not_of(' ');
  if (pos == s.npos)
    return {};
  return s.substr(pos);
}

string_view RStrip(string_view s)
{
  auto it = std::find_if(s.crbegin(), s.crend(), [](auto val)
    {
      return val != ' ';
    });
  if (it == s.crend())
    return {};
  s.remove_suffix(std::distance(s.crbegin(), it));
  return s;
}

string_view Strip(string_view s)
{
  return RStrip(LStrip(s));
}

//constexpr double KmHToMMin(double speedKmH)
//{
//  return speedKmH * 1000. / 60.;
//}

InputStreamWrapper::InputStreamWrapper() :
    _in(nullptr)
{}

InputStreamWrapper::InputStreamWrapper(std::istream& in) :
    _in(&in)
{}

bool InputStreamWrapper::IsNull() const
{
    return _in == nullptr;
}

const std::istream& InputStreamWrapper::GetStream() const
{
    return *_in;
}

std::istream& InputStreamWrapper::GetStream()
{
    return *_in;
}


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

#include <sstream>
#include <iomanip>

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


#include <string>

namespace Json
{
  class Node;

  std::string GetStringByName(const Node& node, const std::string& name);
  double GetDoubleByName(const Node& node, const std::string& name);
  int GetIntByName(const Node& node, const std::string& name);
  bool GetBoolByName(const Node& node, const std::string& name);
}



std::string Json::GetStringByName(const Node& node, const std::string& name)
{
  if (!node.IsMap())
    return {};
  const auto& dict = node.AsMap();
  auto it = dict.find(name);
  if (it == dict.end())
    return {};
  auto stringNode = it->second;
  if (!stringNode.IsString())
    return {};
  return stringNode.AsString();
}

double Json::GetDoubleByName(const Node& node, const std::string& name)
{
  if (!node.IsMap())
    return {};
  const auto& dict = node.AsMap();
  auto it = dict.find(name);
  if (it == dict.end())
    return {};
  auto doubleNode = it->second;
  if (!doubleNode.IsNumber())
    return {};
  return doubleNode.AsDouble();
}

int Json::GetIntByName(const Node& node, const std::string& name)
{
  if (!node.IsMap())
    return {};
  const auto& dict = node.AsMap();
  auto it = dict.find(name);
  if (it == dict.end())
    return {};
  auto intNode = it->second;
  if (!intNode.IsNumber())
    return {};
  return intNode.AsInt();
}

bool Json::GetBoolByName(const Node& node, const std::string& name)
{
  if (!node.IsMap())
    return {};
  const auto& dict = node.AsMap();
  auto it = dict.find(name);
  if (it == dict.end())
    return {};
  auto intNode = it->second;
  if (!intNode.IsBool())
    return {};
  return intNode.AsBool();
  return false;
}



struct Point
{
  double x;
  double y;
};

double CalcDistance(const Point& p1, const Point& p2);

#include <cmath>

double CalcDistance(const Point& p1, const Point& p2)
{
  return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) +
    (p1.y - p2.y) * (p1.y - p2.y));
}


#include <vector>
#include <iostream>

struct GeoPoint
{
  double latitude;
  double longitude;
};

using GeoPointVec = std::vector<GeoPoint>;

double CalcDistance(const GeoPoint& p1, const GeoPoint& p2);
double CalcDistance(const GeoPointVec& points);
std::istream& operator>>(std::istream& in, GeoPoint& p);
bool operator==(const GeoPoint& lhs, const GeoPoint& rhs);
bool operator!=(const GeoPoint& lhs, const GeoPoint& rhs);
#include <cmath>

using namespace std;

constexpr double PI = 3.1415926535;
constexpr double EarthRadius = 6371000.;

namespace
{
  double ToRadians(double degrees)
  {
    return degrees * PI / 180.;
  }
}

double CalcDistance(const GeoPoint& p1, const GeoPoint& p2)
{
  using namespace std;

  GeoPoint p1Radians{ ToRadians(p1.latitude), ToRadians(p1.longitude) };
  GeoPoint p2Radians{ ToRadians(p2.latitude), ToRadians(p2.longitude) };

  double distance = acos(sin(p1Radians.latitude) * sin(p2Radians.latitude) +
    cos(p1Radians.latitude) * cos(p2Radians.latitude)*
    cos(abs(p1Radians.longitude - p2Radians.longitude))) * EarthRadius;
  return distance;
}

double CalcDistance(const GeoPointVec& points)
{
  double distance = 0.;
  for (size_t i = 0; i + 1 < points.size(); i++)
  {
    distance += CalcDistance(points[i], points[i + 1]);
  }
  return distance;
}

istream& operator>>(istream& in, GeoPoint& p)
{
  in >> p.latitude >> p.longitude;
  return in;
}

bool operator==(const GeoPoint& lhs, const GeoPoint& rhs)
{
  return IsEqual(lhs.latitude, rhs.latitude) &&
    IsEqual(lhs.longitude, rhs.longitude);
}

bool operator!=(const GeoPoint& lhs, const GeoPoint& rhs)
{
  return !(lhs == rhs);
}

#include <string>
#include <iostream>
#include <memory.h>

struct Stop
{
  std::string name;
  GeoPoint location;
};
using StopShp = std::shared_ptr<Stop>;

bool operator==(const Stop& lhs, const Stop& rhs);
bool operator!=(const Stop& lhs, const Stop& rhs);


using namespace std;

bool operator==(const Stop& lhs, const Stop& rhs)
{
  return lhs.name == rhs.name &&
    lhs.location == rhs.location;
}

bool operator!=(const Stop& lhs, const Stop& rhs)
{
  return !(lhs == rhs);
}

#include <string>
#include <vector>
#include <optional>
#include <memory>

using StopNames = std::vector<std::string>;

class Route
{
public:
  enum Type
  {
    Common,
    Circular,
  };

  Route(std::string name);
  Route(std::string name, StopNames stops, Type type);

  const std::string& GetName() const;
  void SetName(std::string name);

  const StopNames& GetStopNames() const;
  void SetStopNames(StopNames stops);

  void AddStopName(std::string stopName);

  Type GetType() const;
  void SetType(Type type);

  StopNames GetFullRoute() const;
  int GetNumOfStopsInFullRoute() const;

private:
  StopNames GetFullRouteForCommon() const;
  StopNames GetFullRouteForCircle() const;

private:
  std::string _name;
  StopNames _stops;
  Type _type;
};

bool operator==(const Route& lhs, const Route& rhs);
bool operator!=(const Route& lhs, const Route& rhs);

using RouteShp = std::shared_ptr<Route>;

#include <unordered_set>

using namespace std;

Route::Route(std::string name) :
  Route(std::move(name), {}, Type::Common)
{}

Route::Route(std::string name, StopNames stops, Route::Type type) :
  _name(std::move(name)),
  _stops(std::move(stops)), 
  _type(type)
{}

const std::string& Route::GetName() const
{
  return _name;
}

void Route::SetName(std::string name)
{
  _name = std::move(name);
}

const StopNames& Route::GetStopNames() const
{
  return _stops;
}

void Route::SetStopNames(StopNames stops)
{
  _stops = std::move(stops);
}

void Route::AddStopName(std::string stopName)
{
  _stops.push_back(std::move(stopName));
}

Route::Type Route::GetType() const
{
  return _type;
}

void Route::SetType(Type type)
{
  _type = type;
}

StopNames Route::GetFullRoute() const
{
  if (_type == Route::Common)
  {
    return GetFullRouteForCommon();
  }
  else
  {
    return GetFullRouteForCircle();
  }
}

int Route::GetNumOfStopsInFullRoute() const
{
  if (_type == Route::Common)
  {
    return _stops.size() * 2 - 1;
  }
  else
  {
    return _stops.size();
  }
}

StopNames Route::GetFullRouteForCommon() const
{
  StopNames fullRoute = _stops;
  fullRoute.reserve(GetNumOfStopsInFullRoute());
  for (auto it = std::next(_stops.crbegin()); it != _stops.crend(); it++)
    fullRoute.push_back(*it);
  return fullRoute;
}

StopNames Route::GetFullRouteForCircle() const
{
  return _stops;
}

bool operator==(const Route& lhs, const Route& rhs)
{
    return lhs.GetName() == rhs.GetName() &&
      lhs.GetType() == rhs.GetType() &&
      lhs.GetStopNames() == rhs.GetStopNames();
}

bool operator!=(const Route& lhs, const Route& rhs)
{
  return !(lhs == rhs);
}


#include <cstdint>
#include <memory>

struct RoutingSettings
{
public:
  RoutingSettings() = default;
  ~RoutingSettings() = default;
  uint32_t BusWaitTime{ 0 };
  double BusVelocityKmH{0.};
};


#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <string>
#include <optional>
#include <memory>

using StringVec = std::vector<std::string>;
using StringViewVec = std::vector<std::string_view>;
using FromTo = std::pair<std::string_view, std::string_view>;


struct StopData
{
	StopShp Stop;
	std::vector<RouteShp> Routes;
};
using StopDataShp = std::shared_ptr<StopData>;


class Database
{
public:
  Database() = default;
  ~Database() = default;

  void AddStop(StopShp stop);
  void AddRoute(RouteShp route);

  RouteShp GetRoute(std::string_view routeName) const;
  StopShp GetStop(std::string_view stopName) const;
  std::vector<StopShp> GetStops(std::string_view routeName) const;
  std::vector<StopShp> GetFullRoute(std::string_view routeName) const;
  int GetNumOfStops(std::string_view routeName) const;
  int GetNumOfUniqueStops(std::string_view routeName) const;
  double GetGeographicalRouteLength(std::string_view routeName) const;
  int GetRoadRouteLength(std::string_view routeName) const;
  std::vector<RouteShp> GetRoutesByStop(std::string_view stopName) const;
  void SetRoadLength(std::string_view fromStop, std::string_view toStop, int length);
  int GetRoadLength(std::string_view fromStop, std::string_view toStop) const;

  std::vector<RouteShp> GetAllRoutes() const;
  size_t GetNumOfStops() const;

  const RoutingSettings& GetRoutingSettings() const;
  void SetRoutingSettings(const RoutingSettings& settings);

private:
  std::vector<StopShp> GetStops(const StringVec& stopNames) const;
  std::string_view AddStopName(std::string stopName);
  std::string_view AddRouteName(std::string routeName);
  StopDataShp AddStopData(std::string stopName);

private:
	std::unordered_set<std::string> _stopNames;
	std::unordered_set<std::string> _routeNames;
	std::unordered_map<std::string_view, StopDataShp> _nameToStopData;
	std::unordered_map<std::string_view, RouteShp> _nameToRoute;
	std::map<FromTo, int> _pathToRoadLength; // TODO: Change to unordered_map
  RoutingSettings _routingSettings;
};
using DatabaseShp = std::shared_ptr<Database>;

#include <unordered_set>

using namespace std;

namespace
{
  GeoPointVec MapToGeoPointVec(const vector<StopShp>& stops)
  {
    GeoPointVec vec;
    vec.reserve(stops.size());
    for (const auto& s : stops)
      vec.push_back(s->location);
    return vec;
  }

  template<typename MapK, typename V, typename K>
  V GetByKey(const std::unordered_map<MapK, V>& m, const K& key)
  {
    auto it = m.find(key);
    if (it == m.cend())
      return {};
    return it->second;
  }

  string_view AddString(std::unordered_set<std::string>& s, std::string str)
  {
      auto [it, _] = s.insert(str);
      return *it;
  }

}

void Database::AddStop(StopShp stop)
{
  auto nameView = AddStopName(stop->name);
  auto stopData = AddStopData(stop->name);
  stopData->Stop = std::move(stop);
}

void Database::AddRoute(RouteShp route)
{
    // TODO: Тут нельзя использовать GetByKey, так как он возвращает результат по значению
    for (const auto& stop : route->GetStopNames())
    {
        auto stopData = AddStopData(stop);
        stopData->Routes.push_back(route);
    }
        
    auto nameView = AddRouteName(route->GetName());
    _nameToRoute[nameView] = std::move(route);
}

RouteShp Database::GetRoute(std::string_view routeName) const
{
  return GetByKey(_nameToRoute, routeName);
}

StopShp Database::GetStop(std::string_view stopName) const
{
  auto stopData = GetByKey(_nameToStopData, stopName);
  if (!stopData)
      return {};
  return stopData->Stop;
}

std::vector<StopShp> Database::GetStops(std::string_view routeName) const
{
  auto route = GetRoute(routeName);
  if (!route)
    return {};

  return GetStops(route->GetStopNames());
}

std::vector<StopShp> Database::GetFullRoute(std::string_view routeName) const
{
  auto route = GetRoute(routeName);
  if (!route)
    return {};

  return GetStops(route->GetFullRoute());
}

int Database::GetNumOfStops(std::string_view routeName) const
{
  auto route = GetRoute(routeName);
  if (route == nullptr)
    return 0;

  return route->GetNumOfStopsInFullRoute();
}

int Database::GetNumOfUniqueStops(std::string_view routeName) const
{
  auto route = GetRoute(routeName);
  if (route == nullptr)
    return 0;

  unordered_set<string> uniqueNames;
  for (const auto& name : route->GetStopNames())
    uniqueNames.insert(name);
  return static_cast<int>(uniqueNames.size());
}

double Database::GetGeographicalRouteLength(std::string_view routeName) const
{
  auto stops = GetFullRoute(routeName);
  auto points = MapToGeoPointVec(stops);
  return CalcDistance(points);
}

int Database::GetRoadRouteLength(std::string_view routeName) const
{
    auto stops = GetFullRoute(routeName);
    int result = 0;
    for (size_t i = 0; i + 1 < stops.size(); i++)
    {
        const auto& start = stops[i];
        const auto& finish = stops[i + 1];

        FromTo fromTo(start->name, finish->name);
        result += _pathToRoadLength.at(fromTo);
    }
    return result;
}

std::vector<RouteShp> Database::GetRoutesByStop(string_view stopName) const
{
    auto stopData = GetByKey(_nameToStopData, stopName);
    if (!stopData)
    {
        return {};
    }
    return stopData->Routes;
}

void Database::SetRoadLength(std::string_view fromStop, std::string_view toStop, int length)
{
    fromStop = AddStopName(string(fromStop));
    toStop = AddStopName(string(toStop));

    FromTo path(fromStop, toStop);
    _pathToRoadLength[path] = length;

    FromTo reversePath(toStop, fromStop);
    auto it = _pathToRoadLength.find(reversePath);
    if (it == _pathToRoadLength.end())
    {
        _pathToRoadLength[reversePath] = length;
    }
}

int Database::GetRoadLength(std::string_view fromStop, std::string_view toStop) const
{
    FromTo fromTo(fromStop, toStop);
    auto it = _pathToRoadLength.find(fromTo);
    if (it == _pathToRoadLength.end())
        return -1;
    return it->second;
}

std::vector<RouteShp> Database::GetAllRoutes() const
{
  std::vector<RouteShp> routes;
  routes.reserve(_nameToRoute.size());
  for (const auto& [name, route] : _nameToRoute)
  {
    routes.push_back(route);
  }
  return routes;
}

size_t Database::GetNumOfStops() const
{
  return _stopNames.size();
}

const RoutingSettings& Database::GetRoutingSettings() const
{
  return _routingSettings;
}

void Database::SetRoutingSettings(const RoutingSettings& settings)
{
  _routingSettings = settings;
}

std::vector<StopShp> Database::GetStops(const StringVec& stopNames) const
{
  vector<StopShp> stops;
  stops.reserve(stopNames.size());
  for (const auto& name : stopNames)
  {
    auto stop = GetStop(name);
    if (stop)
    {
      stops.push_back(stop);
    }
    else
    {
      std::cerr << "Database::GetStops() " << "stop is null for name: " << name;
    }
  }
  return stops;
}

std::string_view Database::AddStopName(std::string stopName)
{
    return AddString(_stopNames, std::move(stopName));
    
}

std::string_view Database::AddRouteName(std::string routeName)
{
    return AddString(_routeNames, std::move(routeName));
}

StopDataShp Database::AddStopData(std::string stopName)
{
    auto data = GetByKey(_nameToStopData, stopName);
    if (data)
        return data;
    auto nameView = AddStopName(stopName);
    data = std::make_shared<StopData>();
    _nameToStopData[nameView] = data;
    return data;
}





#include <cstdlib>
#include <deque>
#include <vector>

template <typename It>
class Range {
public:
  using ValueType = typename std::iterator_traits<It>::value_type;

  Range(It begin, It end) : begin_(begin), end_(end) {}
  It begin() const { return begin_; }
  It end() const { return end_; }

private:
  It begin_;
  It end_;
};

namespace Graph {

  using VertexId = size_t;
  using EdgeId = size_t;

  template <typename Weight>
  struct Edge {
    VertexId from;
    VertexId to;
    Weight weight;
  };

  template <typename Weight>
  class DirectedWeightedGraph {
  private:
    using IncidenceList = std::vector<EdgeId>;
    using IncidentEdgesRange = Range<typename IncidenceList::const_iterator>;

  public:
    DirectedWeightedGraph(size_t vertex_count);
    EdgeId AddEdge(const Edge<Weight>& edge);

    size_t GetVertexCount() const;
    size_t GetEdgeCount() const;
    const Edge<Weight>& GetEdge(EdgeId edge_id) const;
    IncidentEdgesRange GetIncidentEdges(VertexId vertex) const;

  private:
    std::vector<Edge<Weight>> edges_;
    std::vector<IncidenceList> incidence_lists_;
  };


  template <typename Weight>
  DirectedWeightedGraph<Weight>::DirectedWeightedGraph(size_t vertex_count) : incidence_lists_(vertex_count) {}

  template <typename Weight>
  EdgeId DirectedWeightedGraph<Weight>::AddEdge(const Edge<Weight>& edge) {
    edges_.push_back(edge);
    const EdgeId id = edges_.size() - 1;
    incidence_lists_[edge.from].push_back(id);
    return id;
  }

  template <typename Weight>
  size_t DirectedWeightedGraph<Weight>::GetVertexCount() const {
    return incidence_lists_.size();
  }

  template <typename Weight>
  size_t DirectedWeightedGraph<Weight>::GetEdgeCount() const {
    return edges_.size();
  }

  template <typename Weight>
  const Edge<Weight>& DirectedWeightedGraph<Weight>::GetEdge(EdgeId edge_id) const {
    return edges_[edge_id];
  }

  template <typename Weight>
  typename DirectedWeightedGraph<Weight>::IncidentEdgesRange
  DirectedWeightedGraph<Weight>::GetIncidentEdges(VertexId vertex) const {
    const auto& edges = incidence_lists_[vertex];
    return {std::begin(edges), std::end(edges)};
  }
}



#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iterator>
#include <optional>
#include <unordered_map>
#include <utility>
#include <vector>

namespace Graph {

  template <typename Weight>
  class Router {
  private:
    using Graph = DirectedWeightedGraph<Weight>;

  public:
    Router(const Graph& graph);

    using RouteId = uint64_t;

    struct RouteInfo {
      RouteId id;
      Weight weight;
      size_t edge_count;
    };

    std::optional<RouteInfo> BuildRoute(VertexId from, VertexId to) const;
    EdgeId GetRouteEdge(RouteId route_id, size_t edge_idx) const;
    void ReleaseRoute(RouteId route_id);

  private:
    const Graph& graph_;

    struct RouteInternalData {
      Weight weight;
      std::optional<EdgeId> prev_edge;
    };
    using RoutesInternalData = std::vector<std::vector<std::optional<RouteInternalData>>>;

    using ExpandedRoute = std::vector<EdgeId>;
    mutable RouteId next_route_id_ = 0;
    mutable std::unordered_map<RouteId, ExpandedRoute> expanded_routes_cache_;

    void InitializeRoutesInternalData(const Graph& graph) {
      const size_t vertex_count = graph.GetVertexCount();
      for (VertexId vertex = 0; vertex < vertex_count; ++vertex) {
        routes_internal_data_[vertex][vertex] = RouteInternalData{0, std::nullopt};
        for (const EdgeId edge_id : graph.GetIncidentEdges(vertex)) {
          const auto& edge = graph.GetEdge(edge_id);
          assert(edge.weight >= 0);
          auto& route_internal_data = routes_internal_data_[vertex][edge.to];
          if (!route_internal_data || route_internal_data->weight > edge.weight) {
            route_internal_data = RouteInternalData{edge.weight, edge_id};
          }
        }
      }
    }

    void RelaxRoute(VertexId vertex_from, VertexId vertex_to,
                    const RouteInternalData& route_from, const RouteInternalData& route_to) {
      auto& route_relaxing = routes_internal_data_[vertex_from][vertex_to];
      const Weight candidate_weight = route_from.weight + route_to.weight;
      if (!route_relaxing || candidate_weight < route_relaxing->weight) {
        route_relaxing = {
            candidate_weight,
            route_to.prev_edge
                ? route_to.prev_edge
                : route_from.prev_edge
        };
      }
    }

    void RelaxRoutesInternalDataThroughVertex(size_t vertex_count, VertexId vertex_through) {
      for (VertexId vertex_from = 0; vertex_from < vertex_count; ++vertex_from) {
        if (const auto& route_from = routes_internal_data_[vertex_from][vertex_through]) {
          for (VertexId vertex_to = 0; vertex_to < vertex_count; ++vertex_to) {
            if (const auto& route_to = routes_internal_data_[vertex_through][vertex_to]) {
              RelaxRoute(vertex_from, vertex_to, *route_from, *route_to);
            }
          }
        }
      }
    }

    RoutesInternalData routes_internal_data_;
  };


  template <typename Weight>
  Router<Weight>::Router(const Graph& graph)
      : graph_(graph),
        routes_internal_data_(graph.GetVertexCount(), std::vector<std::optional<RouteInternalData>>(graph.GetVertexCount()))
  {
    InitializeRoutesInternalData(graph);

    const size_t vertex_count = graph.GetVertexCount();
    for (VertexId vertex_through = 0; vertex_through < vertex_count; ++vertex_through) {
      RelaxRoutesInternalDataThroughVertex(vertex_count, vertex_through);
    }
  }

  template <typename Weight>
  std::optional<typename Router<Weight>::RouteInfo> Router<Weight>::BuildRoute(VertexId from, VertexId to) const {
    const auto& route_internal_data = routes_internal_data_[from][to];
    if (!route_internal_data) {
      return std::nullopt;
    }
    const Weight weight = route_internal_data->weight;
    std::vector<EdgeId> edges;
    for (std::optional<EdgeId> edge_id = route_internal_data->prev_edge;
         edge_id;
         edge_id = routes_internal_data_[from][graph_.GetEdge(*edge_id).from]->prev_edge) {
      edges.push_back(*edge_id);
    }
    std::reverse(std::begin(edges), std::end(edges));

    const RouteId route_id = next_route_id_++;
    const size_t route_edge_count = edges.size();
    expanded_routes_cache_[route_id] = std::move(edges);
    return RouteInfo{route_id, weight, route_edge_count};
  }

  template <typename Weight>
  EdgeId Router<Weight>::GetRouteEdge(RouteId route_id, size_t edge_idx) const {
    return expanded_routes_cache_.at(route_id)[edge_idx];
  }

  template <typename Weight>
  void Router<Weight>::ReleaseRoute(RouteId route_id) {
    expanded_routes_cache_.erase(route_id);
  }

}


#include <string>
#include <vector>
#include <memory>

class IPathElement
{
public:
  enum Type
  {
    Wait,
    Bus,
  };

  virtual ~IPathElement() = default;
  virtual Type GetType() const = 0;
  virtual double GetTime() const = 0;
};
using IPathElementShp = std::shared_ptr<IPathElement>;

bool operator==(const IPathElement& lhs, const IPathElement& rhs);
bool operator!=(const IPathElement& lhs, const IPathElement& rhs);


class AbstractPathElement : public IPathElement
{
public:
  AbstractPathElement(double time);
  double GetTime() const override;

protected:
  double _time;
};

class WaitPathElement : public AbstractPathElement
{
public:
  WaitPathElement(std::string stopName, double waitTime);
  Type GetType() const override;
  const std::string& GetStopName() const;

private:
  std::string _stopName;
};
using WaitPathElementShp = std::shared_ptr<WaitPathElement>;
bool operator==(const WaitPathElement& lhs, const WaitPathElement& rhs);
bool operator!=(const WaitPathElement& lhs, const WaitPathElement& rhs);

class BusPathElement : public AbstractPathElement
{
public:
  BusPathElement(std::string busName,
    std::string fromStopName,
    std::string toStopName,
    double time);
  Type GetType() const override;
  const std::string& GetBusName() const;
  const std::string& FromStopName() const;
  const std::string& ToStopName() const;

private:
  std::string _busName;
  std::string _fromStopName;
  std::string _toStopName;
};
using BusPathElementShp = std::shared_ptr<BusPathElement>;
bool operator==(const BusPathElement& lhs, const BusPathElement& rhs);
bool operator!=(const BusPathElement& lhs, const BusPathElement& rhs);


class Path
{
public:
  Path(double totalTime, std::vector<IPathElementShp> elements = {});
  double GetTotalTime() const;
  const std::vector<IPathElementShp>& GetElements() const;
  void AddElement(IPathElementShp element);

private:
  double _totalTime;
  std::vector<IPathElementShp> _elements;
};
bool operator==(const Path& lhs, const Path& rhs);
bool operator!=(const Path& lhs, const Path& rhs);

#include <cassert>

AbstractPathElement::AbstractPathElement(double time) :
  _time(time)
{}

double AbstractPathElement::GetTime() const
{
  return _time;
}

WaitPathElement::WaitPathElement(std::string stopName, double waitTime) :
  AbstractPathElement(waitTime),
  _stopName(std::move(stopName))
{}

IPathElement::Type WaitPathElement::GetType() const
{
  return Type::Wait;
}

const std::string& WaitPathElement::GetStopName() const
{
  return _stopName;
}

BusPathElement::BusPathElement(std::string busName, std::string fromStopName, std::string toStopName, double time)
  : AbstractPathElement(time),
  _busName(std::move(busName)),
  _fromStopName(std::move(fromStopName)),
  _toStopName(std::move(toStopName))
{}

IPathElement::Type BusPathElement::GetType() const
{
  return Type::Bus;
}

const std::string& BusPathElement::GetBusName() const
{
  return _busName;
}

const std::string& BusPathElement::FromStopName() const
{
  return _fromStopName;
}

const std::string& BusPathElement::ToStopName() const
{
  return _toStopName;
}

Path::Path(double totalTime, std::vector<IPathElementShp> elements) :
  _totalTime(totalTime),
  _elements(std::move(elements))
{}

double Path::GetTotalTime() const
{
  return _totalTime;
}

const std::vector<IPathElementShp>& Path::GetElements() const
{
  return _elements;
}

void Path::AddElement(IPathElementShp element)
{
  _elements.push_back(std::move(element));
}

bool operator==(const IPathElement& lhs, const IPathElement& rhs)
{
  return lhs.GetType() == rhs.GetType() &&
    IsEqual(lhs.GetTime(), rhs.GetTime());
}

bool operator!=(const IPathElement& lhs, const IPathElement& rhs)
{
  return !(lhs == rhs);
}

bool operator==(const WaitPathElement& lhs, const WaitPathElement& rhs)
{
  return static_cast<const IPathElement&>(lhs) == static_cast<const IPathElement&>(rhs) &&
    lhs.GetStopName() == rhs.GetStopName();
}

bool operator!=(const WaitPathElement& lhs, const WaitPathElement& rhs)
{
  return !(lhs == rhs);
}

bool operator==(const BusPathElement& lhs, const BusPathElement& rhs)
{
  return static_cast<const IPathElement&>(lhs) == static_cast<const IPathElement&>(rhs) &&
    lhs.GetBusName() == rhs.GetBusName() &&
    lhs.FromStopName() == rhs.FromStopName() &&
    lhs.ToStopName() == rhs.ToStopName();
}

bool operator!=(const BusPathElement& lhs, const BusPathElement& rhs)
{
  return !(lhs == rhs);
}

bool operator==(const Path& lhs, const Path& rhs)
{
  if (!IsEqual(lhs.GetTotalTime(), rhs.GetTotalTime()))
    return false;
  const auto& lhsElements = lhs.GetElements();
  const auto& rhsElements = rhs.GetElements();
  if (lhsElements.size() != rhsElements.size())
    return false;
  auto size = lhsElements.size();
  for (int i = 0; i < size; i++)
  {
    const auto& lhsElement = lhsElements[i];
    const auto& rhsElement = rhsElements[i];
    if (lhsElement->GetType() != rhsElement->GetType())
      return false;
    if (lhsElement->GetType() == IPathElement::Wait)
    {
      return static_cast<const WaitPathElement&>(*lhsElement) == static_cast<const WaitPathElement&>(*rhsElement);
    }
    else if(lhsElement->GetType() == IPathElement::Bus)
    {
      return static_cast<const BusPathElement&>(*lhsElement) == static_cast<const BusPathElement&>(*rhsElement);
    }
    else
    {
      assert(false);
    }
  }
  return true;
}

bool operator!=(const Path& lhs, const Path& rhs)
{
  return !(lhs == rhs);
}

#include <memory>
#include <string>
#include <string_view>
#include <vector>
#include <optional>
#include <unordered_set>
#include <unordered_map>

class Database;
class Route;
using RouteShp = std::shared_ptr<Route>;
using WeightType = double;

struct VertexData
{
  VertexData() :
    id(0),
    busName(),
    isFinal(false)
  {}

  VertexData(Graph::VertexId id, 
    std::string stopName, 
    std::optional<std::string> busName, 
    bool isFinal) :
    id(id),
    stopName(std::move(stopName)),
    busName(std::move(busName)),
    isFinal(isFinal)
  {}

  Graph::VertexId id;
  std::string stopName;
  std::optional<std::string> busName;
  bool isFinal;
  // bool isDummy?
};
using VertexDataShp = std::shared_ptr<VertexData>;


class PathSearcher
{
  using RouteGraph = Graph::DirectedWeightedGraph<WeightType>;
  using RouteGraphUnp = std::unique_ptr<RouteGraph>;
  using RouteEdge = Graph::Edge<WeightType>;
  using GraphRouter = Graph::Router<WeightType>;
  using GraphRouterUnp = std::unique_ptr<GraphRouter>;

public:
  PathSearcher();
  std::optional<Path> FindPath(const std::string& fromStopName, const std::string& toStopName);

  void Initialize(const Database& db, const RoutingSettings& settings);

private:
  void BuildGraph();
  void InitializeRouter();

  size_t CalculateVertexNum(const std::vector<RouteShp>& routes, size_t stopsNum) const;
  void BuildSubgraphForRoute(const Route& route);
  void BuildSubgraphForCommonRoute(const Route& route);
  void BuildSubgraphForCircleRoute(const Route& route);

  template<typename It>
  void BuildSubgraphForDirectRoute(const std::string& routeName, Range<It>& stopNames);

  // ребра-пересадки
  void BuildTransferEdges();

  void BuildDummyStartStopVertices();

  VertexDataShp CreateVertex(
    std::string stopName,
    std::optional<std::string> busName = std::nullopt ,
    bool isFinal = false);

  VertexDataShp CreateDummyVertex(
    std::string stopName,
    std::optional<std::string> busName = std::nullopt,
    bool isFinal = false);

  RouteEdge CreateEdge(const VertexData& from, const VertexData& to, WeightType weight);
  RouteEdge CreateEdge(Graph::VertexId fromId, Graph::VertexId toId, WeightType weight);

  double CalculateTimeBetweenStops(std::string_view from, std::string_view to) const;
  Graph::VertexId GetNextVertexId() const;

  std::optional<Graph::VertexId> GetStartDummyVertex(const std::string& stopName);
  std::optional<Graph::VertexId> GetFinishDummyVertex(const std::string& stopName);

  bool IsWaitEdge(const VertexData& from, const VertexData& to) const;

private:
  static const WeightType ZeroWeight;

  const Database* _db;
  RoutingSettings _routeSettings;
  RouteGraphUnp _graph;
  GraphRouterUnp _router;
  std::vector<VertexDataShp> _idToVertex;
  mutable Graph::VertexId _nextVertexId;
  std::unordered_map<std::string, std::unordered_set<Graph::VertexId>> _stopNameToVertices;

  struct StartFinishPair
  {
    Graph::VertexId start;
    Graph::VertexId finish;
  };
  std::unordered_map<std::string, StartFinishPair> _stopNameToDummyStartStopVertexId;
};
using PathSearcherShp = std::shared_ptr<PathSearcher>;
using PathSearcherWkp = std::weak_ptr<PathSearcher>;


template<typename It>
void PathSearcher::BuildSubgraphForDirectRoute(const std::string& routeName, Range<It>& stopNames)
{
  if (stopNames.begin() == stopNames.end())
    return;

  auto firstStopVertex = CreateVertex(*stopNames.begin(), routeName, true);
  VertexData* fromVertex = firstStopVertex.get();
  for (auto it = std::next(stopNames.begin()); it != stopNames.end(); it++)
  {
    const auto& stopName = *it;
    auto toVertex = CreateVertex(stopName, routeName, false);
    auto edge = CreateEdge(*fromVertex,
      *toVertex,
      CalculateTimeBetweenStops(fromVertex->stopName, toVertex->stopName));
    _graph->AddEdge(edge);
    fromVertex = toVertex.get();
  }
  fromVertex->isFinal = true;
}

#include <optional>
#include <cassert>

namespace
{
  class GraphRouteRAII
  {
  public:
    GraphRouteRAII(std::optional<typename Graph::Router<WeightType>::RouteInfo> routeInfo,
      Graph::Router<WeightType>* router) :
      _routeInfo(std::move(routeInfo)),
      _router(router)
    {}
    ~GraphRouteRAII()
    {
      if (_router == nullptr)
        return;
      if (!_routeInfo.has_value())
        return;
      _router->ReleaseRoute(_routeInfo->id);
    }

    const std::optional<typename Graph::Router<WeightType>::RouteInfo>& GetRouteInfo() const
    {
      return _routeInfo;
    }
    
  private:
    std::optional<typename Graph::Router<WeightType>::RouteInfo> _routeInfo;
    Graph::Router<WeightType>* _router;
  };
}

const WeightType PathSearcher::ZeroWeight = 0.;

PathSearcher::PathSearcher() :
  _db(nullptr),
  _routeSettings(),
  _graph(),
  _router(),
  _idToVertex(),
  _nextVertexId(0)
{}

std::optional<Path> PathSearcher::FindPath(const std::string& fromStopName, const std::string& toStopName)
{
  auto fromId = GetStartDummyVertex(fromStopName);
  auto toId = GetFinishDummyVertex(toStopName);
  if (!fromId || !toId)
    return std::nullopt;

  // Route завернуть в RAII
  GraphRouteRAII graphRouteRAII(_router->BuildRoute(*fromId, *toId), _router.get());
  const auto& routeInfo = graphRouteRAII.GetRouteInfo();
  if (!routeInfo.has_value())
    return std::nullopt;

  assert(routeInfo->edge_count >= 2);
  size_t startIdx = 1; // skip start dummy vertex
  size_t finishIdx = routeInfo->edge_count - 1; // skip finish dummy vertex
  double totalWeight = routeInfo->weight;

  std::vector<IPathElementShp> pathElements;
  if (startIdx < finishIdx)
  {
    auto edgeId = _router->GetRouteEdge(routeInfo->id, startIdx);
    auto edge = _graph->GetEdge(edgeId);
    auto fromVertexData = _idToVertex[edge.from];
    auto waitElement = std::make_shared<WaitPathElement>(fromVertexData->stopName, _routeSettings.BusWaitTime);
    pathElements.push_back(std::move(waitElement));
    totalWeight += _routeSettings.BusWaitTime;
  }

  for (size_t i = startIdx; i < finishIdx; i++)
  {
    auto edgeId = _router->GetRouteEdge(routeInfo->id, i);
    auto edge = _graph->GetEdge(edgeId);
    auto fromVertexData = _idToVertex[edge.from];
    auto toVertexData = _idToVertex[edge.to];
    IPathElementShp pathElement;
    if (IsWaitEdge(*fromVertexData, *toVertexData))
    {
      pathElement = std::make_shared<WaitPathElement>(toVertexData->stopName, _routeSettings.BusWaitTime);
    }
    else
    {
      assert(toVertexData->busName.has_value());
      pathElement = std::make_shared<BusPathElement>(*toVertexData->busName,
        fromVertexData->stopName,
        toVertexData->stopName,
        edge.weight);
    }
    pathElements.push_back(std::move(pathElement));
  }


  return Path(totalWeight, std::move(pathElements));
}

void PathSearcher::Initialize(const Database& db, const RoutingSettings& settings)
{
  _db = &db;
  _routeSettings = settings;
  BuildGraph();
  InitializeRouter();
}

void PathSearcher::BuildGraph()
{
  auto routes = _db->GetAllRoutes();
  auto totalStopsNum = _db->GetNumOfStops();
  auto vertexNum = CalculateVertexNum(routes, totalStopsNum);
  _graph = std::make_unique<RouteGraph>(vertexNum);
  _idToVertex.resize(vertexNum);

  for (const auto& r : routes)
  {
    BuildSubgraphForRoute(*r);
  }
  BuildTransferEdges();
  BuildDummyStartStopVertices();
}

void PathSearcher::InitializeRouter()
{
  assert(_graph);
  _router = std::make_unique<GraphRouter>(*_graph);
}

size_t PathSearcher::CalculateVertexNum(const std::vector<RouteShp>& routes, size_t stopsNum) const
{
  size_t totalVertexNum = 0;
  for (const auto& r : routes)
  {
    auto numOfStopsInFullRoute = r->GetNumOfStopsInFullRoute();
    if (r->GetType() == Route::Common)
    {
      totalVertexNum += numOfStopsInFullRoute + 1;
    }
    else
    {
      totalVertexNum += (numOfStopsInFullRoute - 1) * 2;
    }
  }
  // dummy vertex
  totalVertexNum += stopsNum * 2;
  return totalVertexNum;
}

void PathSearcher::BuildSubgraphForRoute(const Route& route)
{
  if (route.GetType() == Route::Common)
  {
    BuildSubgraphForCommonRoute(route);
  }
  else
  {
    BuildSubgraphForCircleRoute(route);
  }
}

void PathSearcher::BuildSubgraphForCommonRoute(const Route& route)
{
  const auto& stopNames = route.GetStopNames();
  Range directStopNames(stopNames.cbegin(), stopNames.cend());
  BuildSubgraphForDirectRoute(route.GetName(), directStopNames);
  Range reverseStopNames(stopNames.crbegin(), stopNames.crend());
  BuildSubgraphForDirectRoute(route.GetName(), reverseStopNames);
}

void PathSearcher::BuildSubgraphForCircleRoute(const Route& route)
{
  auto stopNames = route.GetFullRoute();
  auto firstStopVertex = CreateVertex(stopNames.front(), route.GetName(), true);
  VertexData* fromVertex = firstStopVertex.get();
  for (auto it = std::next(stopNames.cbegin()); it != stopNames.cend(); it++)
  {
    const auto& stopName = *it;
    auto toVertex = CreateVertex(stopName, route.GetName(), false);
    auto edge = CreateEdge(*fromVertex,
      *toVertex,
      CalculateTimeBetweenStops(fromVertex->stopName, toVertex->stopName));
    _graph->AddEdge(edge);
    fromVertex = toVertex.get();
  }
  fromVertex->isFinal = true;
  // Пересадка на первой конечке
  _graph->AddEdge(CreateEdge(*fromVertex, *firstStopVertex, _routeSettings.BusWaitTime));
}

void PathSearcher::BuildTransferEdges()
{
  // TODO: Сделать читаемым
  for (const auto& [stopName, verticesIds] : _stopNameToVertices)
  {
    if (verticesIds.size() < 2)
      continue;

    auto prevEndIt = std::prev(verticesIds.cend());
    for (auto i = verticesIds.cbegin(); i != prevEndIt; i++)
    {
      for (auto j = std::next(i); j != verticesIds.cend(); j++)
      {
        _graph->AddEdge(CreateEdge(*i, *j, _routeSettings.BusWaitTime));
        _graph->AddEdge(CreateEdge(*j, *i, _routeSettings.BusWaitTime));
      }
    }
  }
}

void PathSearcher::BuildDummyStartStopVertices()
{
  for (const auto& [stopName, verticesIds] : _stopNameToVertices)
  {
    auto dummyStart = CreateDummyVertex(stopName);
    auto dummyFinish = CreateDummyVertex(stopName);
    _stopNameToDummyStartStopVertexId[stopName] = StartFinishPair{ dummyStart->id, dummyFinish->id };

    for (const auto id : verticesIds)
    {
      _graph->AddEdge(CreateEdge(dummyStart->id, id, ZeroWeight));
      _graph->AddEdge(CreateEdge(id, dummyFinish->id, ZeroWeight));
    }
  }
}

VertexDataShp PathSearcher::CreateVertex(
  std::string stopName, 
  std::optional<std::string> busName, 
  bool isFinal)
{
  auto v = CreateDummyVertex(std::move(stopName), std::move(busName), isFinal);
  _stopNameToVertices[v->stopName].insert(v->id);
  return v;
}

VertexDataShp PathSearcher::CreateDummyVertex(
  std::string stopName, 
  std::optional<std::string> busName, 
  bool isFinal)
{
  auto v = std::make_shared<VertexData>();
  v->id = GetNextVertexId();
  v->stopName = std::move(stopName);
  v->busName = std::move(busName),
    v->isFinal = isFinal;
  _idToVertex[v->id] = v;
  return v;
}

PathSearcher::RouteEdge PathSearcher::CreateEdge(const VertexData& from, const VertexData& to, WeightType weight)
{
  return CreateEdge(from.id, to.id, weight);
}

PathSearcher::RouteEdge PathSearcher::CreateEdge(Graph::VertexId fromId, Graph::VertexId toId, WeightType weight)
{
  RouteEdge edge;
  edge.from = fromId;
  edge.to = toId;
  edge.weight = weight;
  return edge;
}

double PathSearcher::CalculateTimeBetweenStops(std::string_view from, std::string_view to) const
{
  auto roadLengthMeters = _db->GetRoadLength(from, to);
  return roadLengthMeters / KmHToMMin(_routeSettings.BusVelocityKmH);
}

Graph::VertexId PathSearcher::GetNextVertexId() const
{
  return _nextVertexId++;
}

std::optional<Graph::VertexId> PathSearcher::GetStartDummyVertex(const std::string& stopName)
{
  auto it = _stopNameToDummyStartStopVertexId.find(stopName);
  if (it == _stopNameToDummyStartStopVertexId.end())
    return std::nullopt;
  return it->second.start;
}

std::optional<Graph::VertexId> PathSearcher::GetFinishDummyVertex(const std::string& stopName)
{
  auto it = _stopNameToDummyStartStopVertexId.find(stopName);
  if (it == _stopNameToDummyStartStopVertexId.end())
    return std::nullopt;
  return it->second.finish;
}

bool PathSearcher::IsWaitEdge(const VertexData& from, const VertexData& to) const
{
  return from.stopName == to.stopName;
}





#include <memory>
#include <iostream>

enum class RequestType
{
	InputBus,
	InputStop,
	OutputBus,
	OutputStop,
	RoutingSettings,
	FindRoute
};
inline std::ostream& operator<<(std::ostream& out, RequestType requestType)
{
	out << static_cast<int>(requestType);
	return out;
}


class IRequest
{
public:
	virtual ~IRequest() = default;
	virtual RequestType GetType() const = 0;
};
using IRequestShp = std::shared_ptr<IRequest>;

#include <memory>

class AbstractOutputRequest : public IRequest
{
public:
	AbstractOutputRequest();
	virtual ~AbstractOutputRequest() = default;

	int GetId() const;
	void SetId(int id);

protected:
	int _id;
};
using AbstractOutputRequestShp = std::shared_ptr< AbstractOutputRequest>;


AbstractOutputRequest::AbstractOutputRequest() :
    _id(-1)
{}

int AbstractOutputRequest::GetId() const
{
    return _id;
}

void AbstractOutputRequest::SetId(int id)
{
    _id = id;
}


#include <string>

class OutputBusRequest : public AbstractOutputRequest
{
public:
	virtual ~OutputBusRequest() = default;

	RequestType GetType() const override;

	const std::string& GetName() const;
	void SetName(std::string name);

private:
	std::string _name;
};
using OutputBusRequestShp = std::shared_ptr<OutputBusRequest>;

bool operator==(const OutputBusRequest& lhs, const OutputBusRequest& rhs);
bool operator!=(const OutputBusRequest& lhs, const OutputBusRequest& rhs);

RequestType OutputBusRequest::GetType() const
{
	return RequestType::OutputBus;
}

const std::string& OutputBusRequest::GetName() const
{
	return _name;
}

void OutputBusRequest::SetName(std::string name)
{
	_name = std::move(name);
}

bool operator==(const OutputBusRequest& lhs, const OutputBusRequest& rhs)
{
	return IsEqual(lhs.GetId(), rhs.GetId()) &&
		IsEqual(lhs.GetName(), rhs.GetName());
}

bool operator!=(const OutputBusRequest& lhs, const OutputBusRequest& rhs)
{
	return !(lhs == rhs);
}


#include <string>

class OutputStopRequest : public AbstractOutputRequest
{
public:
	virtual ~OutputStopRequest() = default;

	RequestType GetType() const override;

	const std::string& GetName() const;
	void SetName(std::string name);

private:
	std::string _name;
};
using OutputStopRequestShp = std::shared_ptr<OutputStopRequest>;

bool operator==(const OutputStopRequest& lhs, const OutputStopRequest& rhs);
bool operator!=(const OutputStopRequest& lhs, const OutputStopRequest& rhs);

RequestType OutputStopRequest::GetType() const
{
    return RequestType::OutputStop;
}

const std::string& OutputStopRequest::GetName() const
{
    return _name;
}

void OutputStopRequest::SetName(std::string name)
{
    _name = std::move(name);
}

bool operator==(const OutputStopRequest& lhs, const OutputStopRequest& rhs)
{
  return IsEqual(lhs.GetId(), rhs.GetId()) &&
    IsEqual(lhs.GetName(), rhs.GetName());
}

bool operator!=(const OutputStopRequest& lhs, const OutputStopRequest& rhs)
{
  return !(lhs == rhs);
}


#include <string>
#include <vector>

class InputBusRequest : public IRequest
{
public:
	InputBusRequest();
	virtual ~InputBusRequest() = default;

	RequestType GetType() const override;

	const std::string& GetName() const;
	void SetName(std::string name);

	const StringVec& GetStops() const;
	void SetStops(StringVec stops);

	Route::Type GetBusType() const;
	void SetBusType(Route::Type type);

private:
	std::string _name;
	StringVec _stops;
	Route::Type _busType;
};
using InputBusRequestShp = std::shared_ptr <InputBusRequest>;

bool operator==(const InputBusRequest& lhs, const InputBusRequest& rhs);
bool operator!=(const InputBusRequest& lhs, const InputBusRequest& rhs);

InputBusRequest::InputBusRequest() :
	_name(),
	_stops(),
	_busType(Route::Common)
{
}

RequestType InputBusRequest::GetType() const
{
	return RequestType::InputBus;
}

const std::string& InputBusRequest::GetName() const
{
	return _name;
}

void InputBusRequest::SetName(std::string name)
{
	_name = std::move(name);
}

const StringVec& InputBusRequest::GetStops() const
{
	return _stops;
}

void InputBusRequest::SetStops(StringVec stops)
{
	_stops = std::move(stops);
}

Route::Type InputBusRequest::GetBusType() const
{
	return _busType;
}

void InputBusRequest::SetBusType(Route::Type type)
{
	_busType = type;
}

bool operator==(const InputBusRequest& lhs, const InputBusRequest& rhs)
{
	return IsEqual(lhs.GetName(), rhs.GetName()) &&
		IsEqual(lhs.GetStops(), rhs.GetStops()) &&
		IsEqual(lhs.GetBusType(), rhs.GetBusType());
}

bool operator!=(const InputBusRequest& lhs, const InputBusRequest& rhs)
{
	return !(lhs == rhs);
}


#include <unordered_map>
#include <string>

class InputStopRequest : public IRequest
{
public:
	InputStopRequest();
	virtual ~InputStopRequest() = default;

	RequestType GetType() const override;

	const std::string& GetName() const;
	void SetName(std::string name);

	double GetLatitude() const;
	void SetLatitude(double latitude);

	double GetLongitude() const;
	void SetLongitude(double longitude);

	const std::unordered_map<std::string, int>& GetStopToLength() const;
	void SetStopToLength(std::unordered_map<std::string, int> stopToLength);
	void AddLengthToStop(std::string stop, int length);

private:
	std::string _name;
	double _latitude;
	double _longitude;
	std::unordered_map<std::string, int> _stopToLength;
};
using InputStopRequestShp = std::shared_ptr<InputStopRequest>;

bool operator==(const InputStopRequest& lhs, const InputStopRequest& rhs);
bool operator!=(const InputStopRequest& lhs, const InputStopRequest& rhs);

InputStopRequest::InputStopRequest() :
	_name(),
	_latitude(0.),
	_longitude(0.),
	_stopToLength()
{}

RequestType InputStopRequest::GetType() const
{
	return RequestType::InputStop;
}

const std::string& InputStopRequest::GetName() const
{
	return _name;
}

void InputStopRequest::SetName(std::string name)
{
	_name = std::move(name);
}

double InputStopRequest::GetLatitude() const
{
	return _latitude;
}

void InputStopRequest::SetLatitude(double latitude)
{
	_latitude = latitude;
}

double InputStopRequest::GetLongitude() const
{
	return _longitude;
}

void InputStopRequest::SetLongitude(double longitude)
{
	_longitude = longitude;
}

const std::unordered_map<std::string, int>& InputStopRequest::GetStopToLength() const
{
	return _stopToLength;
}

void InputStopRequest::SetStopToLength(std::unordered_map<std::string, int> stopToLength)
{
	_stopToLength = std::move(stopToLength);
}

void InputStopRequest::AddLengthToStop(std::string stop, int length)
{
	_stopToLength[std::move(stop)] = length;
}

bool operator==(const InputStopRequest& lhs, const InputStopRequest& rhs)
{
	return IsEqual(lhs.GetName(), rhs.GetName()) &&
		IsEqual(lhs.GetLatitude(), rhs.GetLatitude()) &&
		IsEqual(lhs.GetLongitude(), rhs.GetLongitude()) &&
		IsEqual(lhs.GetStopToLength(), rhs.GetStopToLength());
}

bool operator!=(const InputStopRequest& lhs, const InputStopRequest& rhs)
{
	return !(lhs == rhs);
}


class RoutingSettingsRequest : public IRequest
{
public:
  RoutingSettingsRequest();
  RoutingSettingsRequest(int busWaitTime, double busVelocity);
  virtual ~RoutingSettingsRequest() = default;

  RequestType GetType() const override;

  int GetBusWaitTime() const;
  void SetBusWaitTime(int time);

  double GetBusVelocity() const;
  void SetBusVelocity(double velocity);

private:
  int _busWaitTime;
  double _busVelocity;
};
using RoutingSettingsRequestShp = std::shared_ptr<RoutingSettingsRequest>;



RoutingSettingsRequest::RoutingSettingsRequest() :
  RoutingSettingsRequest(0, 0.)
{}

RoutingSettingsRequest::RoutingSettingsRequest(int busWaitTime, double busVelocity) :
  _busWaitTime(busWaitTime),
  _busVelocity(busVelocity)
{}

RequestType RoutingSettingsRequest::GetType() const
{
  return RequestType::RoutingSettings;
}

int RoutingSettingsRequest::GetBusWaitTime() const
{
  return _busWaitTime;
}

void RoutingSettingsRequest::SetBusWaitTime(int time)
{
  _busWaitTime = time;
}

double RoutingSettingsRequest::GetBusVelocity() const
{
  return _busVelocity;
}

void RoutingSettingsRequest::SetBusVelocity(double velocity)
{
  _busVelocity = velocity;
}



class FindRouteRequest : public AbstractOutputRequest
{
public:
	virtual ~FindRouteRequest() = default;

	RequestType GetType() const override;

	const std::string& GetFromStop() const;
	void SetFromStop(std::string name);

	const std::string& GetToStop() const;
	void SetToStop(std::string name);

private:
	std::string _fromStop;
	std::string _toStop;
};
using FindRouteRequestShp = std::shared_ptr<FindRouteRequest>;

bool operator==(const FindRouteRequest& lhs, const FindRouteRequest& rhs);
bool operator!=(const FindRouteRequest& lhs, const FindRouteRequest& rhs);


RequestType FindRouteRequest::GetType() const
{
    return RequestType::FindRoute;
}

const std::string& FindRouteRequest::GetFromStop() const
{
  return _fromStop;
}

void FindRouteRequest::SetFromStop(std::string name)
{
  _fromStop = std::move(name);
}

const std::string& FindRouteRequest::GetToStop() const
{
  return _toStop;
}

void FindRouteRequest::SetToStop(std::string name)
{
  _toStop = std::move(name);
}

bool operator==(const FindRouteRequest& lhs, const FindRouteRequest& rhs)
{
  return lhs.GetFromStop() == rhs.GetFromStop() &&
    lhs.GetToStop() == rhs.GetToStop();
}

bool operator!=(const FindRouteRequest& lhs, const FindRouteRequest& rhs)
{
  return !(lhs == rhs);
}


#include <memory>

class IResponse
{
public:
  virtual ~IResponse() = default;
  virtual RequestType GetType() const = 0;
};
using IResponseShp = std::shared_ptr<IResponse>;


class AbstractResponse : public IResponse
{
public:
  AbstractResponse(RequestType type);
  RequestType GetType() const override;

protected:
  RequestType _type;
};
using AbstractResponseShp = std::shared_ptr<AbstractResponse>;

class AbstractOutputResponse : public AbstractResponse
{
public:
  using AbstractResponse::AbstractResponse;

  int GetId() const;
  void SetId(int id);

protected:
  int _id = 0;
};
using AbstractOutputResponseShp = std::shared_ptr<AbstractOutputResponse>;


AbstractResponse::AbstractResponse(RequestType type) :
  _type(type)
{
}

RequestType AbstractResponse::GetType() const
{
  return _type;
}

int AbstractOutputResponse::GetId() const
{
  return _id;
}

void AbstractOutputResponse::SetId(int id)
{
  _id = id;
}



class OutputBusResponse : public AbstractOutputResponse
{
public:
  OutputBusResponse();

  const std::string& GetRouteName() const;
  void SetRouteName(std::string name);

  bool HasRoute() const;

  const RouteShp& GetRoute() const;
  void SetRoute(RouteShp route);

  int GetStopsOnRouteNum() const;
  void SetStopsOnRouteNum(int numOfStops);

  int GetUniqueStopsNum() const;
  void SetUniqueStopsNum(int num);

  double GetGeographicalRouteLength() const;
  void SetGeographicalRouteLength(double length);

  int GetRoadRouteLength() const;
  void SetRoadRouteLength(int length);

  double GetCurvature() const;
  void SetCurvature(double curvature);

private:
  RouteShp _route;
  int _stopsOnRouteNum;
  int _uniqueStopsNum;
  double _geographicalRouteLength;
  int _roadRouteLength;
  double _curvature;
  std::string _routeName;
};
using OutputBusResponseShp = std::shared_ptr<OutputBusResponse>;



OutputBusResponse::OutputBusResponse() :
  AbstractOutputResponse(RequestType::OutputBus),
  _route(nullptr),
  _stopsOnRouteNum(0),
  _uniqueStopsNum(0),
  _geographicalRouteLength(0.),
  _roadRouteLength(0),
  _curvature(0.),
  _routeName()
{
}

const std::string& OutputBusResponse::GetRouteName() const
{
  return _routeName;
}

void OutputBusResponse::SetRouteName(std::string name)
{
  _routeName = std::move(name);
}

bool OutputBusResponse::HasRoute() const
{
  return _route != nullptr;
}

const RouteShp& OutputBusResponse::GetRoute() const
{
  return _route;
}

void OutputBusResponse::SetRoute(RouteShp route)
{
  _route = std::move(route);
}

int OutputBusResponse::GetStopsOnRouteNum() const
{
  return _stopsOnRouteNum;
}

void OutputBusResponse::SetStopsOnRouteNum(int numOfStops)
{
  _stopsOnRouteNum = numOfStops;
}

int OutputBusResponse::GetUniqueStopsNum() const
{
  return _uniqueStopsNum;
}

void OutputBusResponse::SetUniqueStopsNum(int num)
{
  _uniqueStopsNum = num;
}

double OutputBusResponse::GetGeographicalRouteLength() const
{
  return _geographicalRouteLength;
}

void OutputBusResponse::SetGeographicalRouteLength(double length)
{
  _geographicalRouteLength = length;
}

int OutputBusResponse::GetRoadRouteLength() const
{
  return _roadRouteLength;
}

void OutputBusResponse::SetRoadRouteLength(int length)
{
  _roadRouteLength = length;
}

double OutputBusResponse::GetCurvature() const
{
  return _curvature;
}

void OutputBusResponse::SetCurvature(double curvature)
{
  _curvature = curvature;
}


#include <vector>

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


OutputStopResponse::OutputStopResponse() : 
  AbstractOutputResponse(RequestType::OutputStop),
  _stopName(),
  _stop(nullptr),
  _routes()
{
}

const std::string& OutputStopResponse::GetStopName() const
{
  return _stopName;
}

void OutputStopResponse::SetStopName(std::string name)
{
  _stopName = std::move(name);
}

bool OutputStopResponse::IsStopExist() const
{
  return _stop != nullptr;
}

const StopShp& OutputStopResponse::GetStop() const
{
  return _stop;
}

void OutputStopResponse::SetStop(StopShp stop)
{
  _stop = std::move(stop);
}

bool OutputStopResponse::HasRoutes() const
{
  return !_routes.empty();
}

const std::vector<RouteShp>& OutputStopResponse::GetRoutes() const
{
  return _routes;
}

void OutputStopResponse::SetRoutes(std::vector<RouteShp> routes)
{
  _routes = std::move(routes);
}

bool operator==(const OutputStopResponse& lhs, const OutputStopResponse& rhs)
{
  return IsEqual(lhs.GetId(), rhs.GetId()) &&
    IsEqual(lhs.GetStopName(), rhs.GetStopName()) &&
    IsEqual(lhs.GetStop(), rhs.GetStop()) &&
    IsEqual(lhs.GetRoutes(), rhs.GetRoutes());
}

bool operator!=(const OutputStopResponse& lhs, const OutputStopResponse& rhs)
{
  return !(lhs == rhs);
}


class InputBusResponse : public AbstractResponse
{
public:
  InputBusResponse();

};
using InputBusResponseShp = std::shared_ptr< InputBusResponse>;

bool operator==(const InputBusResponse& lhs, const InputBusResponse& rhs);
bool operator!=(const InputBusResponse& lhs, const InputBusResponse& rhs);


InputBusResponse::InputBusResponse() : AbstractResponse(RequestType::InputBus)
{
}

bool operator==(const InputBusResponse& lhs, const InputBusResponse& rhs)
{
    return true;
}

bool operator!=(const InputBusResponse& lhs, const InputBusResponse& rhs)
{
  return !(lhs == rhs);
}


class InputStopResponse : public AbstractResponse
{
public:
  InputStopResponse();
};
using InputStopResponseShp = std::shared_ptr<InputStopResponse>;

bool operator==(const InputStopResponse& lhs, const InputStopResponse& rhs);
bool operator!=(const InputStopResponse& lhs, const InputStopResponse& rhs);


InputStopResponse::InputStopResponse() : AbstractResponse(RequestType::InputStop)
{
}

bool operator==(const InputStopResponse& lhs, const InputStopResponse& rhs)
{
  return true;
}

bool operator!=(const InputStopResponse& lhs, const InputStopResponse& rhs)
{
  return !(lhs == rhs);
}


#include <optional>

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




FindRouteResponse::FindRouteResponse() :
  AbstractOutputResponse(RequestType::FindRoute)
{}

const std::optional<Path>& FindRouteResponse::GetPath() const
{
  return _path;
}

void FindRouteResponse::SetPath(std::optional<Path> path)
{
  _path = std::move(path);
}

bool operator==(const FindRouteResponse& lhs, const FindRouteResponse& rhs)
{
  return IsEqual(lhs.GetPath(), rhs.GetPath());
}

bool operator!=(const FindRouteResponse& lhs, const FindRouteResponse& rhs)
{
  return !(lhs == rhs);
}


#include <memory>
#include <iostream>
#include <functional>

class IRequestStreamParser
{
public:
	virtual ~IRequestStreamParser() = default;

	virtual void SetRequestStream(std::istream& in) = 0;
	virtual bool HasRequest() const = 0;
	virtual IRequestShp GetNextRequest() = 0;
};
using IRequestStreamParserShp = std::shared_ptr<IRequestStreamParser>;

#include<string>
#include<memory>

namespace Json
{
	class Node;

	class IRequestParser
	{
	public:
		virtual ~IRequestParser() = default;

		virtual const std::string& GetRequestName() const = 0;
		virtual IRequestShp Parse(const Node& node) = 0;
	};
	using IRequestParserShp = std::shared_ptr<IRequestParser>;
}

#include <string>

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



#include <string>

using namespace Json;
using namespace std;

std::string Json::AbstractRequestParser::GetStringByName(const Node& node, const std::string& name) const
{
  return ::GetStringByName(node, name);
}

double Json::AbstractRequestParser::GetDoubleByName(const Node& node, const std::string& name) const
{
  return ::GetDoubleByName(node, name);
}

int Json::AbstractRequestParser::GetIntByName(const Node& node, const std::string& name) const
{
  return ::GetIntByName(node, name);
}

bool Json::AbstractRequestParser::GetBoolByName(const Node& node, const std::string& name) const
{
  return ::GetBoolByName(node, name);
}

#include <string>
#include <vector>

using StringVec = std::vector<std::string>;

namespace Json
{
  class OutputBusRequestParser : public AbstractRequestParser
  {
  public:
    const std::string& GetRequestName() const override;
    IRequestShp Parse(const Node& node) override;

  protected:
    int GetId(const Node& node) const;
    std::string GetName(const Node& node) const;
  };
  using OutputBusRequestParserShp = std::shared_ptr<OutputBusRequestParser>;


  class OutputStopRequestParser : public AbstractRequestParser
  {
  public:
    const std::string& GetRequestName() const override;
    IRequestShp Parse(const Node& node) override;

  protected:
    int GetId(const Node& node) const;
    std::string GetName(const Node& node) const;
  };
  using OutputStopRequestParserShp = std::shared_ptr<OutputStopRequestParser>;


  class InputBusRequestParser : public AbstractRequestParser
  {
  public:
    const std::string& GetRequestName() const override;
    IRequestShp Parse(const Node& node) override;

  protected:
    std::string GetName(const Node& node) const;
    StringVec GetStops(const Node& node) const;
    Route::Type GetRouteType(const Node& node) const;
  };
  using InputBusRequestParserShp = std::shared_ptr<InputBusRequestParser>;


  class InputStopRequestParser : public AbstractRequestParser
  {
  public:
    const std::string& GetRequestName() const override;
    IRequestShp Parse(const Node& node) override;

  protected:
    std::string GetName(const Node& node) const;
    std::unordered_map<std::string, int> GetRoadToDistance(const Node& node) const;
    double GetLongitude(const Node& node) const;
    double GetLatitude(const Node& node) const;
  };
  using InputStopRequestParserShp = std::shared_ptr<InputStopRequestParser>;


  class InputRoutingSettingsParser : public AbstractRequestParser
  {
  public:
    const std::string& GetRequestName() const override;
    IRequestShp Parse(const Node& node) override;
  };
  using InputRoutingSettingsParserShp = std::shared_ptr<InputRoutingSettingsParser>;


  class FindRouteRequestParser : public AbstractRequestParser
  {
  public:
    const std::string& GetRequestName() const override;
    IRequestShp Parse(const Node& node) override;

  protected:
    int GetId(const Node& node) const;
    std::string GetFrom(const Node& node) const;
    std::string GetTo(const Node& node) const;
  };
  using FindRouteRequestParserShp = std::shared_ptr<FindRouteRequestParser>;
}


#include <string>

using namespace Json;
using namespace std;

const std::string& Json::OutputBusRequestParser::GetRequestName() const
{
  static string name = "Bus";
  return name;
}

IRequestShp Json::OutputBusRequestParser::Parse(const Node& node)
{
  if (!node.IsMap())
    return {};

  auto request = std::make_shared<OutputBusRequest>();
  request->SetId(GetId(node));
  request->SetName(GetName(node));
  return request;
}

int Json::OutputBusRequestParser::GetId(const Node& node) const
{
  return GetIntByName(node, "id");
}

std::string Json::OutputBusRequestParser::GetName(const Node& node) const
{
  return GetStringByName(node, "name");
}


const std::string& Json::OutputStopRequestParser::GetRequestName() const
{
  static string name = "Stop";
  return name;
}

IRequestShp Json::OutputStopRequestParser::Parse(const Node& node)
{
  if (!node.IsMap())
    return {};

  auto request = std::make_shared<OutputStopRequest>();
  request->SetId(GetId(node));
  request->SetName(GetName(node));
  return request;
}

int Json::OutputStopRequestParser::GetId(const Node& node) const
{
  return GetIntByName(node, "id");
}

std::string Json::OutputStopRequestParser::GetName(const Node& node) const
{
  return GetStringByName(node, "name");
}



const std::string& Json::InputBusRequestParser::GetRequestName() const
{
  static string name = "Bus";
  return name;
}

IRequestShp Json::InputBusRequestParser::Parse(const Node& node)
{
  if (!node.IsMap())
    return {};

  auto request = std::make_shared<InputBusRequest>();
  request->SetName(GetName(node));
  request->SetStops(GetStops(node));
  request->SetBusType(GetRouteType(node));
  return request;
}

std::string Json::InputBusRequestParser::GetName(const Node& node) const
{
  return GetStringByName(node, "name");
}

StringVec Json::InputBusRequestParser::GetStops(const Node& node) const
{
  if (!node.IsMap())
    return {};
  const auto& dict = node.AsMap();
  auto it = dict.find("stops");
  if (it == dict.end())
    return {};

  auto arrNode = it->second;
  if (!arrNode.IsArray())
    return {};
  auto arr = arrNode.AsArray();
  StringVec stops;
  stops.reserve(arr.size());
  for (const auto& n : arr)
  {
    if (!n.IsString())
      continue;
    stops.push_back(n.AsString());
  }
  return stops;
}

Route::Type Json::InputBusRequestParser::GetRouteType(const Node& node) const
{
  bool is_roundtrip = GetBoolByName(node, "is_roundtrip");
  return is_roundtrip ? Route::Circular : Route::Common;
}



const std::string& Json::InputStopRequestParser::GetRequestName() const
{
  static string name = "Stop";
  return name;
}

IRequestShp Json::InputStopRequestParser::Parse(const Node& node)
{
  if (!node.IsMap())
    return {};

  auto request = std::make_shared<InputStopRequest>();
  request->SetName(GetName(node));
  request->SetStopToLength(GetRoadToDistance(node));
  request->SetLongitude(GetLongitude(node));
  request->SetLatitude(GetLatitude(node));
  
  return request;
}

std::string Json::InputStopRequestParser::GetName(const Node& node) const
{
  return GetStringByName(node, "name");
}

std::unordered_map<std::string, int> Json::InputStopRequestParser::GetRoadToDistance(const Node& node) const
{
  if (!node.IsMap())
    return {};
  const auto& dict = node.AsMap();
  auto it = dict.find("road_distances");
  if (it == dict.end())
    return {};

  auto mapNode = it->second;
  if (!mapNode.IsMap())
    return {};
  auto nameToNodes = mapNode.AsMap();
  std::unordered_map<std::string, int> roadToDistance;
  for (const auto& [name, node] : nameToNodes)
  {
    if (!node.IsInt())
      continue;
    roadToDistance[name] = node.AsInt();
  }

  return roadToDistance;
}

double Json::InputStopRequestParser::GetLongitude(const Node& node) const
{
  return GetDoubleByName(node, "longitude");
}

double Json::InputStopRequestParser::GetLatitude(const Node& node) const
{
  return GetDoubleByName(node, "latitude");
}

const std::string& Json::InputRoutingSettingsParser::GetRequestName() const
{
  static string name = "routing_settings";
  return name;
}

IRequestShp Json::InputRoutingSettingsParser::Parse(const Node& node)
{
  if (!node.IsMap())
    return {};

  auto request = std::make_shared<RoutingSettingsRequest>();
  request->SetBusVelocity(GetDoubleByName(node, "bus_velocity"));
  request->SetBusWaitTime(GetIntByName(node, "bus_wait_time"));
  return request;
}

const std::string& FindRouteRequestParser::GetRequestName() const
{
  static string name = "Route";
  return name;
}

IRequestShp FindRouteRequestParser::Parse(const Node& node)
{
  if (!node.IsMap())
    return {};

  auto request = std::make_shared<FindRouteRequest>();
  request->SetId(GetId(node));
  request->SetFromStop(GetFrom(node));
  request->SetToStop(GetTo(node));
  return request;
}

int FindRouteRequestParser::GetId(const Node& node) const
{
  return GetIntByName(node, "id");
}

std::string FindRouteRequestParser::GetFrom(const Node& node) const
{
  return GetStringByName(node, "from");
}

std::string FindRouteRequestParser::GetTo(const Node& node) const
{
  return GetStringByName(node, "to");
}


#include <unordered_map>
#include <list>
#include <tuple>
#include <functional>

namespace Json
{
	class IRequestParser;
	using IRequestParserShp = std::shared_ptr<IRequestParser>;

	class Section
	{
	public:
		Section(std::string name, Node node);
		Section(std::string name, std::vector<Node> nodes);

		bool IsEnd() const;
		void ToNextNode();
		const Node& GetCurrNode() const;

		const std::string& GetName() const;

	private:
		std::vector<Node> _nodes;
		size_t _currNodeIndex;
		std::string _name;
	};

	class RequestStreamParser : public IRequestStreamParser
	{
		using ParsersMap = std::unordered_map<std::string, IRequestParserShp>;
		using ParseNodeFunc = std::function<IRequestShp(const Node& node)>;
	public:
		using OnBaseRequestsParsedCb = std::function<void()>;

		RequestStreamParser();
		virtual ~RequestStreamParser() = default;

		void SetRequestStream(std::istream& in) override;
		bool HasRequest() const override;
		IRequestShp GetNextRequest() override;

		void RegisterRoutingSettingsParser(IRequestParserShp parser);
		void RegisterInputRequestsParser(IRequestParserShp parser);
		void RegisterOutputRequestsParser(IRequestParserShp parser);

		void AddOnBaseRequestsParsedCb(OnBaseRequestsParsedCb cb);

	private:
		void ToStartState();
		void AddRoutingSettingsSection(const Node& rootNode);
		void AddBaseRequestsSection(const Node& rootNode);
		void AddStatRequestsSection(const Node& rootNode);
		void RemoveEmptySections();
		std::vector<Node> GetArrByName(const Node& rootNode, const std::string& name) const;
		Node GetObjByName(const Node& rootNode, const std::string& name) const;

		IRequestShp GetNextRequest(
			const Node& node,
			const std::unordered_map<std::string, IRequestParserShp>& parsers) const;
		IRequestShp GetNextRequest(
			const Node& node,
			const IRequestParserShp& parser) const;
		std::string GetType(const Node& node) const;
		void OnBaseRequestsParsed();


	private:
		std::list<std::pair<Section, ParseNodeFunc>> _sections;
		IRequestParserShp _routingSettingsParser;
		ParsersMap _baseParsers;
		ParsersMap _statParsers;

		std::vector<OnBaseRequestsParsedCb> _onBaseRequestsParsedCbs;
	};
	using RequestStreamParserShp = std::shared_ptr<RequestStreamParser>;
}



using namespace std;
using namespace Json;

namespace
{
  static const std::string& RoutingSettingsSectionName("routing_settings");
  static const std::string& BaseRequestsSectionName("base_requests");
  static const std::string& StatRequestsSectionName("stat_requests");

}

Json::Section::Section(std::string name, Node node) :
  Section(std::move(name), std::vector<Node>{std::move(node)})
{
}

Json::Section::Section(std::string name, std::vector<Node> nodes) :
  _nodes(std::move(nodes)),
  _currNodeIndex(0),
  _name(std::move(name))
{}

bool Json::Section::IsEnd() const
{
  return _currNodeIndex >= _nodes.size();
}

void Json::Section::ToNextNode()
{
  _currNodeIndex++;
}

const Node& Json::Section::GetCurrNode() const
{
  return _nodes[_currNodeIndex];
}

const std::string& Json::Section::GetName() const
{
  return _name;
}

Json::RequestStreamParser::RequestStreamParser() :
  _sections(),
  _routingSettingsParser(),
  _baseParsers(),
  _statParsers()
{}

void Json::RequestStreamParser::SetRequestStream(std::istream& in)
{
  ToStartState();
  auto doc = Load(in);
  const auto& rootNode = doc.GetRoot();
  AddRoutingSettingsSection(rootNode);
  AddBaseRequestsSection(rootNode);
  AddStatRequestsSection(rootNode);
  RemoveEmptySections();
}

bool Json::RequestStreamParser::HasRequest() const
{
  for (const auto& [section, _] : _sections)
  {
    if (!section.IsEnd())
      return true;
  }
  return false;
}

IRequestShp Json::RequestStreamParser::GetNextRequest()
{
  if (!HasRequest())
    return {};
  auto& [section, parseFunc] = _sections.front();
  IRequestShp request = parseFunc(section.GetCurrNode());
  section.ToNextNode();
  if (section.IsEnd())
  {
    if (section.GetName() == BaseRequestsSectionName)
      OnBaseRequestsParsed();
    _sections.pop_front();
  }
  return request;
}

void Json::RequestStreamParser::RegisterRoutingSettingsParser(IRequestParserShp parser)
{
  if (parser != nullptr)
    _routingSettingsParser = std::move(parser);
}

void Json::RequestStreamParser::RegisterInputRequestsParser(IRequestParserShp parser)
{
  if(parser != nullptr)
    _baseParsers[parser->GetRequestName()] = std::move(parser);
}

void Json::RequestStreamParser::RegisterOutputRequestsParser(IRequestParserShp parser)
{
  if (parser != nullptr)
    _statParsers[parser->GetRequestName()] = std::move(parser);
}

void RequestStreamParser::AddOnBaseRequestsParsedCb(OnBaseRequestsParsedCb cb)
{
  _onBaseRequestsParsedCbs.push_back(cb);
}

void Json::RequestStreamParser::ToStartState()
{
  _sections.clear();
}

void Json::RequestStreamParser::AddRoutingSettingsSection(const Node& rootNode)
{
  auto parseRoutingSettings = [this](const Node& node)
    {
      if (_routingSettingsParser == nullptr)
        return IRequestShp();
      return GetNextRequest(node, _routingSettingsParser);
    };
  _sections.emplace_back(
    Section(RoutingSettingsSectionName, GetObjByName(rootNode, RoutingSettingsSectionName)),
          parseRoutingSettings);
}

void Json::RequestStreamParser::AddBaseRequestsSection(const Node& rootNode)
{
  auto parseBaseRequest = [this](const Node& node)
    {
      return GetNextRequest(node, _baseParsers);
    };
  _sections.emplace_back(
    Section(BaseRequestsSectionName, GetArrByName(rootNode, BaseRequestsSectionName)), parseBaseRequest);
}

void Json::RequestStreamParser::AddStatRequestsSection(const Node& rootNode)
{
  auto parseStatRequest = [this](const Node& node)
    {
      return GetNextRequest(node, _statParsers);
    };
  _sections.emplace_back(
    Section(StatRequestsSectionName, GetArrByName(rootNode, StatRequestsSectionName)), parseStatRequest);
}

void Json::RequestStreamParser::RemoveEmptySections()
{
  _sections.remove_if([](const auto& section)
    {
      return section.first.IsEnd();
    });
}

std::vector<Node> Json::RequestStreamParser::GetArrByName(const Node& rootNode, const std::string& name) const
{
  if (!rootNode.IsMap())
    return {};
  const auto& dict = rootNode.AsMap();
  auto it = dict.find(name);
  if (it == dict.end())
    return {};

  auto arrNode = it->second;
  if (!arrNode.IsArray())
    return {};
  return arrNode.AsArray();
}

Node Json::RequestStreamParser::GetObjByName(const Node& rootNode, const std::string& name) const
{
  if (!rootNode.IsMap())
    return {};
  const auto& dict = rootNode.AsMap();
  auto it = dict.find(name);
  if (it == dict.end())
    return {};
  return it->second;
}

IRequestShp Json::RequestStreamParser::GetNextRequest(
  const Node& node,
  const std::unordered_map<std::string, IRequestParserShp>& parsers) const
{
  auto type = GetType(node);
  auto it = parsers.find(type);
  if (it == parsers.end())
    return {};
  return GetNextRequest(node, it->second);
}

IRequestShp Json::RequestStreamParser::GetNextRequest(
  const Node& node,
  const IRequestParserShp& parser) const
{
  return parser->Parse(node);
}

std::string Json::RequestStreamParser::GetType(const Node& node) const
{
  return GetStringByName(node, "type");
}

void RequestStreamParser::OnBaseRequestsParsed()
{
  for (const auto& cb : _onBaseRequestsParsedCbs)
    cb();
}


#include <memory>

class IRequest;
class IResponse;
using IResponseShp = std::shared_ptr<IResponse>;

class IRequestExecutor
{
public:
  virtual ~IRequestExecutor() = default;

  virtual IResponseShp Execute(const IRequest* request) = 0;

};
using IRequestExecutorShp = std::shared_ptr<IRequestExecutor>;


class ISpecificRequestExecutor : public IRequestExecutor
{
public:
  ~ISpecificRequestExecutor() = default;

  virtual RequestType GetRequestType() const = 0;
};
using ISpecificRequestExecutorShp = std::shared_ptr<ISpecificRequestExecutor>;



class InputBusRequest;
class Database;
using DatabaseShp = std::shared_ptr<Database>;


class InputBusRequestExecutor : public ISpecificRequestExecutor
{
public:
  InputBusRequestExecutor(DatabaseShp db);

  RequestType GetRequestType() const override;
  IResponseShp Execute(const IRequest* request) override;

private:
  const InputBusRequest* ToInputBusRequest(const IRequest* request) const;

private:
  DatabaseShp _db;
};
using InputBusRequestExecutorShp = std::shared_ptr<InputBusRequestExecutor>;


InputBusRequestExecutor::InputBusRequestExecutor(DatabaseShp db) :
  _db(std::move(db))
{
}

RequestType InputBusRequestExecutor::GetRequestType() const
{
  return RequestType::InputBus;
}

IResponseShp InputBusRequestExecutor::Execute(const IRequest* request)
{
  auto r = ToInputBusRequest(request);
  if (r == nullptr)
    return {};

  auto route = std::make_shared<Route>(r->GetName(), r->GetStops(), r->GetBusType());
  _db->AddRoute(std::move(route));

  auto response = std::make_shared<InputBusResponse>();
  return response;
}

const InputBusRequest* InputBusRequestExecutor::ToInputBusRequest(const IRequest* request) const
{
  return dynamic_cast<const InputBusRequest*>(request);
}



class InputStopRequest;
class Database;
using DatabaseShp = std::shared_ptr<Database>;

class InputStopRequestExecutor : public ISpecificRequestExecutor
{
public:
  InputStopRequestExecutor(DatabaseShp db);

  RequestType GetRequestType() const override;
  IResponseShp Execute(const IRequest* request) override;

private:
  const InputStopRequest* ToInputStopRequest(const IRequest* request) const;

private:
  DatabaseShp _db;
};
using InputStopRequestExecutorShp = std::shared_ptr<InputStopRequestExecutor>;


InputStopRequestExecutor::InputStopRequestExecutor(DatabaseShp db) :
  _db(std::move(db))
{
}

RequestType InputStopRequestExecutor::GetRequestType() const
{
  return RequestType::InputStop;
}

IResponseShp InputStopRequestExecutor::Execute(const IRequest* request)
{
  auto r = ToInputStopRequest(request);

  auto stop = std::make_shared<Stop>();
  stop->name = r->GetName();
  stop->location = GeoPoint{r->GetLatitude(), r->GetLongitude()};
  _db->AddStop(std::move(stop));

  for (const auto& [toStop, length] : r->GetStopToLength())
  {
    _db->SetRoadLength(r->GetName(), toStop, length);
  }

  auto response = std::make_shared<InputStopResponse>();
  return response;
}

const InputStopRequest* InputStopRequestExecutor::ToInputStopRequest(const IRequest* request) const
{
  return dynamic_cast<const InputStopRequest*>(request);
}



class OutputBusRequest;
class Database;
using DatabaseShp = std::shared_ptr<Database>;

class OutputBusRequestExecutor : public ISpecificRequestExecutor
{
public:
  OutputBusRequestExecutor(DatabaseShp db);

  RequestType GetRequestType() const override;
  IResponseShp Execute(const IRequest* request) override;

private:
  const OutputBusRequest* ToOutputBusRequest(const IRequest* request) const;

private:
  DatabaseShp _db;
};
using OutputBusRequestExecutorShp = std::shared_ptr< OutputBusRequestExecutor>;


OutputBusRequestExecutor::OutputBusRequestExecutor(DatabaseShp db) :
  _db(std::move(db))
{}

RequestType OutputBusRequestExecutor::GetRequestType() const
{
  return RequestType::OutputBus;
}

IResponseShp OutputBusRequestExecutor::Execute(const IRequest* request)
{
  auto outputBusRequest = ToOutputBusRequest(request);
  if (outputBusRequest == nullptr)
    return {};

  auto response = std::make_shared<OutputBusResponse>();
  const auto& routeName = outputBusRequest->GetName();
  response->SetId(outputBusRequest->GetId());
  response->SetRouteName(routeName);
  response->SetRoute(_db->GetRoute(routeName));
  if (response->GetRoute() == nullptr)
  {
    return response;
  }

  auto stopsOnRouteNum = _db->GetNumOfStops(routeName);
  auto uniqueStopsNum = _db->GetNumOfUniqueStops(routeName);
  auto geographicalRouteLength = _db->GetGeographicalRouteLength(routeName);
  auto roadRouteLength = _db->GetRoadRouteLength(routeName);
  double curvature = roadRouteLength / geographicalRouteLength;

  response->SetStopsOnRouteNum(stopsOnRouteNum);
  response->SetUniqueStopsNum(uniqueStopsNum);
  response->SetGeographicalRouteLength(geographicalRouteLength);
  response->SetRoadRouteLength(roadRouteLength);
  response->SetCurvature(curvature);
  return response;
}

const OutputBusRequest* OutputBusRequestExecutor::ToOutputBusRequest(const IRequest* request) const
{
    return dynamic_cast<const OutputBusRequest*>(request);
}



class OutputStopRequest;
class Database;
using DatabaseShp = std::shared_ptr<Database>;

class OutputStopRequestExecutor : public ISpecificRequestExecutor
{
public:
  OutputStopRequestExecutor(DatabaseShp db);

  RequestType GetRequestType() const override;
  IResponseShp Execute(const IRequest* request) override;

private:
  const OutputStopRequest* ToOutputStopRequest(const IRequest* request) const;

private:
  DatabaseShp _db;
};



OutputStopRequestExecutor::OutputStopRequestExecutor(DatabaseShp db) :
  _db(std::move(db))
{
}

RequestType OutputStopRequestExecutor::GetRequestType() const
{
  return RequestType::OutputStop;
}

IResponseShp OutputStopRequestExecutor::Execute(const IRequest* request)
{
  auto r = ToOutputStopRequest(request);
	auto response = std::make_shared<OutputStopResponse>();
	response->SetId(r->GetId());

	const auto& stopName = r->GetName();
	response->SetStopName(stopName);
	response->SetStop(_db->GetStop(stopName));
	if (response->IsStopExist())
		response->SetRoutes(_db->GetRoutesByStop(stopName));
	
  return response;
}

const OutputStopRequest* OutputStopRequestExecutor::ToOutputStopRequest(const IRequest* request) const
{
  return dynamic_cast<const OutputStopRequest*>(request);
}


class RoutingSettingsRequest;
class Database;
using DatabaseShp = std::shared_ptr<Database>;

class RoutingSettingsRequestExecutor : public ISpecificRequestExecutor
{
public:
  RoutingSettingsRequestExecutor(DatabaseShp db);
  RequestType GetRequestType() const override;
  IResponseShp Execute(const IRequest* request) override;

private:
  const RoutingSettingsRequest* ToRoutingSettingsRequest(const IRequest* request) const;

private:
  DatabaseShp _db;
};
using RoutingSettingsRequestExecutorShp = std::shared_ptr<RoutingSettingsRequestExecutor>;


RoutingSettingsRequestExecutor::RoutingSettingsRequestExecutor(DatabaseShp db) :
  _db(std::move(db))
{}

RequestType RoutingSettingsRequestExecutor::GetRequestType() const
{
  return RequestType::RoutingSettings;
}

IResponseShp RoutingSettingsRequestExecutor::Execute(const IRequest* request)
{
  auto r = ToRoutingSettingsRequest(request);
  if (r == nullptr)
    return {};

  RoutingSettings settings;
  settings.BusVelocityKmH = r->GetBusVelocity();
  settings.BusWaitTime = r->GetBusWaitTime();
  _db->SetRoutingSettings(settings);

  return {};
}

const RoutingSettingsRequest* RoutingSettingsRequestExecutor::ToRoutingSettingsRequest(const IRequest* request) const
{
  return dynamic_cast<const RoutingSettingsRequest*>(request);
}


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




FindRouteRequestExecutor::FindRouteRequestExecutor(DatabaseShp db, PathSearcherShp pathSearcher) :
  _db(std::move(db)),
  _pathSearcher(std::move(pathSearcher))
{
}

RequestType FindRouteRequestExecutor::GetRequestType() const
{
  return RequestType::FindRoute;
}

IResponseShp FindRouteRequestExecutor::Execute(const IRequest* request)
{
  auto findRouteRequest = dynamic_cast<const FindRouteRequest*>(request);
  if (findRouteRequest == nullptr)
    return {};

  auto response = std::make_shared<FindRouteResponse>();
  response->SetId(findRouteRequest->GetId());
  response->SetPath(
    _pathSearcher->FindPath(findRouteRequest->GetFromStop(), findRouteRequest->GetToStop()));
  return response;
}


#include <unordered_map>

class RequestStreamExecutor : public IRequestExecutor
{
public:
  RequestStreamExecutor() = default;
  IResponseShp Execute(const IRequest* request) override;

  void RegisterExecutor(ISpecificRequestExecutorShp executor);

protected:
  std::unordered_map<RequestType, ISpecificRequestExecutorShp> _requestExecutors;
};



IResponseShp RequestStreamExecutor::Execute(const IRequest* request)
{
  if (request == nullptr)
    return {};

  auto it = _requestExecutors.find(request->GetType());
  if (it == _requestExecutors.end())
    return {};

  auto& executor = it->second;
  return executor->Execute(request);
}

void RequestStreamExecutor::RegisterExecutor(ISpecificRequestExecutorShp executor)
{
  if (executor == nullptr)
    return;
  _requestExecutors[executor->GetRequestType()] = std::move(executor);
}


#include <memory>
#include <iostream>

class IResponseStreamFormatter
{
public:
  virtual ~IResponseStreamFormatter() = default;

  virtual void Start(std::ostream& out) = 0;
  virtual void Format(const IResponse& response) = 0;
  virtual void Finish() = 0;

};
using IResponseStreamFormatterShp = std::shared_ptr<IResponseStreamFormatter>;


#include <memory>
#include <map>
#include <unordered_map>
#include <string>

class IResponse;
class OutputBusResponse;
class OutputStopResponse;
class InputBusResponse;
class InputStopResponse;
class FindRouteResponse;
class Route;
using RouteShp = std::shared_ptr<Route>;
class WaitPathElement;

namespace Json
{
  class IResponseFormatter
  {
  public:
    virtual ~IResponseFormatter() = default;

    virtual RequestType GetType() = 0;
    virtual Node Format(const IResponse* response) = 0;
  };
  using IResponseFormatterShp = std::shared_ptr<IResponseFormatter>;

  class OutputBusResponseFormatter : public IResponseFormatter
  {
  public:
    OutputBusResponseFormatter() = default;

    RequestType GetType() override;
    Node Format(const IResponse* response) override;

  private:
    void FormatIfRouteNotFound(const OutputBusResponse* r);
    void DefaultFormat(const OutputBusResponse* r);
    void FormatCommonPart(const OutputBusResponse* r);
    void ClearPreviousState();

  private:
    std::map<std::string, Node> _responseNode;
  };
  using OutputBusResponseFormatterShp = std::shared_ptr<OutputBusResponseFormatter>;


  class OutputStopResponseFormatter : public IResponseFormatter
  {
  public:
    OutputStopResponseFormatter() = default;

    RequestType GetType() override;
    Node Format(const IResponse* response) override;

  private:
    void FormatStopNotFound(const OutputStopResponse* response);
    void SuccessFormat(const OutputStopResponse* response);
    void FormatCommonPart(const OutputStopResponse* r);
    Node CreateNodeForRoutes(const std::vector<RouteShp>& routes);
    void ClearPreviousState();

  private:
    std::map<std::string, Node> _responseNode;
  };
  using OutputStopResponseFormatterShp = std::shared_ptr<OutputStopResponseFormatter>;


  class InputBusResponseFormatter : public IResponseFormatter
  {
  public:
    InputBusResponseFormatter() = default;

    RequestType GetType() override;
    Node Format(const IResponse* response) override;
  };
  using InputBusResponseFormatterShp = std::shared_ptr<InputBusResponseFormatter>;


  class InputStopResponseFormatter : public IResponseFormatter
  {
  public:
    InputStopResponseFormatter() = default;

    RequestType GetType() override;
    Node Format(const IResponse* response) override;
  };
  using InputStopResponseFormatterShp = std::shared_ptr<InputStopResponseFormatter>;


  class FindRouteResponseFormatter : public IResponseFormatter
  {
    struct BusItemData
    {
      std::string BusName;
      int BusSpanCount = 0;
      double BusTotalTime = 0.;
    };
  public:
    FindRouteResponseFormatter() = default;

    RequestType GetType() override;
    Node Format(const IResponse* response) override;

  private:
    void ClearPreviousState();
    void FormatRouteNotFound(const FindRouteResponse* r);
    void FormatRouteFound(const FindRouteResponse* r);
    void FormatCommonPart(const FindRouteResponse* r);

    Node CreateBusItem(const BusItemData& busItemData) const;
    Node CreateWaitItem(const WaitPathElement& waitElement) const;

  private:
    std::map<std::string, Node> _responseNode;
  };
  using FindRouteResponseFormatterShp = std::shared_ptr<FindRouteResponseFormatter>;


  class ResponseStreamFormatter : public IResponseStreamFormatter
  {
  public:
    ResponseStreamFormatter();
    void Start(std::ostream& out) override;
    void Format(const IResponse& response) override;
    void Finish() override;

    void RegisterResponseFormatter(IResponseFormatterShp formatter);

  protected:
    std::ostream* _out;
    std::vector<Node> _rootNode;
    std::unordered_map<RequestType, IResponseFormatterShp> _formatters;
  };
  using ResponseStreamFormatterShp = std::shared_ptr<ResponseStreamFormatter>;
}


#include <string>
#include <set>
#include <cassert>

using namespace Json;
using namespace std;

RequestType Json::OutputBusResponseFormatter::GetType()
{
  return RequestType::OutputBus;
}

Node Json::OutputBusResponseFormatter::Format(const IResponse* response)
{
  ClearPreviousState();
  auto r = dynamic_cast<const OutputBusResponse*>(response);
  if (r == nullptr)
    return {};

  if (r->GetRoute() == nullptr)
  {
    FormatIfRouteNotFound(r);
  }
  else
  {
    DefaultFormat(r);
  }
  return Node(_responseNode);
}

void Json::OutputBusResponseFormatter::FormatIfRouteNotFound(const OutputBusResponse* r)
{
  FormatCommonPart(r);
  _responseNode["error_message"] = "not found"s;
}

void Json::OutputBusResponseFormatter::DefaultFormat(const OutputBusResponse* r)
{
  FormatCommonPart(r);

  _responseNode["stop_count"] = r->GetStopsOnRouteNum();
  _responseNode["unique_stop_count"] = r->GetUniqueStopsNum();
  _responseNode["route_length"] = r->GetRoadRouteLength();
  _responseNode["curvature"] = r->GetCurvature();
}

void Json::OutputBusResponseFormatter::FormatCommonPart(const OutputBusResponse* r)
{
  _responseNode["request_id"] = r->GetId();
}

void Json::OutputBusResponseFormatter::ClearPreviousState()
{
  _responseNode.clear();
}


RequestType Json::OutputStopResponseFormatter::GetType()
{
  return RequestType::OutputStop;
}

Node Json::OutputStopResponseFormatter::Format(const IResponse* response)
{
  ClearPreviousState();
  auto r = dynamic_cast<const OutputStopResponse*>(response);
  if (r == nullptr)
    return {};

  if (!r->IsStopExist())
  {
    FormatStopNotFound(r);
  }
  else
  {
    SuccessFormat(r);
  }
  return Node(_responseNode);
}

void Json::OutputStopResponseFormatter::FormatStopNotFound(const OutputStopResponse* r)
{
  FormatCommonPart(r);
  _responseNode["error_message"] = "not found"s;
}

void Json::OutputStopResponseFormatter::SuccessFormat(const OutputStopResponse* r)
{
  FormatCommonPart(r);
  _responseNode["buses"] = CreateNodeForRoutes(r->GetRoutes());
}

void Json::OutputStopResponseFormatter::FormatCommonPart(const OutputStopResponse* r)
{
  _responseNode["request_id"] = r->GetId();
}

Node Json::OutputStopResponseFormatter::CreateNodeForRoutes(const std::vector<RouteShp>& routes)
{
  std::set<std::string> sortedRoutes;
  for (const auto& r : routes)
    sortedRoutes.insert(r->GetName());

  std::vector<Node> nodes;
  for (const auto& rName : sortedRoutes)
  {
    nodes.push_back(rName);
  }
  return Node(nodes);
}

void Json::OutputStopResponseFormatter::ClearPreviousState()
{
  _responseNode.clear();
}

RequestType Json::InputBusResponseFormatter::GetType()
{
  return RequestType::InputBus;
}

Node Json::InputBusResponseFormatter::Format(const IResponse* response)
{
  return Node();
}


RequestType Json::InputStopResponseFormatter::GetType()
{
  return RequestType::InputStop;
}

Node Json::InputStopResponseFormatter::Format(const IResponse* response)
{
  return Node();
}

RequestType Json::FindRouteResponseFormatter::GetType()
{
  return RequestType::FindRoute;
}

Node Json::FindRouteResponseFormatter::Format(const IResponse* response)
{
  ClearPreviousState();
  auto r = dynamic_cast<const FindRouteResponse*>(response);
  if (r == nullptr)
    return {};

  if (!r->GetPath().has_value())
  {
    FormatRouteNotFound(r);
  }
  else
  {
    FormatRouteFound(r);
  }
  return Node(_responseNode);
}

void Json::FindRouteResponseFormatter::ClearPreviousState()
{
  _responseNode.clear();
}

void Json::FindRouteResponseFormatter::FormatRouteNotFound(const FindRouteResponse* r)
{
  FormatCommonPart(r);
  _responseNode.insert(std::make_pair("error_message", std::string("not found")));
}

void Json::FindRouteResponseFormatter::FormatRouteFound(const FindRouteResponse* r)
{
  FormatCommonPart(r);
  const auto& path = *r->GetPath();
  _responseNode.insert(std::make_pair("total_time", path.GetTotalTime()));

  std::vector<Node> items;
  BusItemData busItemData;

  const auto &elements = path.GetElements();
  for (const auto& e : elements)
  {
    if (e->GetType() == IPathElement::Wait)
    {
      if (busItemData.BusSpanCount != 0)
      {
        items.push_back(CreateBusItem(busItemData));
        busItemData = {};
      }

      auto waitElement = std::dynamic_pointer_cast<WaitPathElement>(e);
      if (waitElement)
        items.push_back(CreateWaitItem(*waitElement));
    }
    else if (e->GetType() == IPathElement::Bus)
    {
      auto busElement = std::dynamic_pointer_cast<BusPathElement>(e);
      if (busElement)
      {
        if (busItemData.BusName.empty())
          busItemData.BusName = busElement->GetBusName();
        busItemData.BusSpanCount++;
        busItemData.BusTotalTime += busElement->GetTime();
      }
    }
    else
    {
      assert(0);
    }
  }

  if (busItemData.BusSpanCount != 0)
  {
    items.push_back(CreateBusItem(busItemData));
  }
  _responseNode.insert(std::make_pair("items", items));
}

void Json::FindRouteResponseFormatter::FormatCommonPart(const FindRouteResponse* r)
{
  _responseNode["request_id"] = r->GetId();
}
Node Json::FindRouteResponseFormatter::CreateBusItem(const BusItemData& busItemData) const
{
  std::map<std::string, Node> busItem;
  busItem.insert(std::make_pair("type", std::string("Bus")));
  busItem.insert(std::make_pair("bus", busItemData.BusName));
  busItem.insert(std::make_pair("span_count", busItemData.BusSpanCount));
  busItem.insert(std::make_pair("time", busItemData.BusTotalTime));
  return busItem;
}

Node Json::FindRouteResponseFormatter::CreateWaitItem(const WaitPathElement& waitElement) const
{
  std::map<std::string, Node> waitItem =
  {
    std::make_pair("type", Node(std::string("Wait"))),
    std::make_pair("stop_name", Node(waitElement.GetStopName())),
    std::make_pair("time", Node(waitElement.GetTime()))
  };
  return waitItem;
}


Json::ResponseStreamFormatter::ResponseStreamFormatter() :
  _out(nullptr),
  _rootNode(),
  _formatters()
{
}

void Json::ResponseStreamFormatter::Start(std::ostream& out)
{
  _out = &out;
}

void Json::ResponseStreamFormatter::Format(const IResponse& response)
{
  auto formatterIt = _formatters.find(response.GetType());
  if (formatterIt == _formatters.end())
    return;

  const auto& formatter = formatterIt->second;
  auto node = formatter->Format(&response);
  if(!node.IsEmpty())
    _rootNode.push_back(std::move(node));
}

void Json::ResponseStreamFormatter::Finish()
{
  Document doc(_rootNode);
  (*_out) << doc.ToJson();
}

void Json::ResponseStreamFormatter::RegisterResponseFormatter(IResponseFormatterShp formatter)
{
  if (formatter != nullptr)
    _formatters[formatter->GetType()] = formatter;
}



#include <memory>

class IRequestStreamHandler
{
public:
  virtual ~IRequestStreamHandler() = default;

  virtual void Handle() = 0;

};
using IRequestStreamHandlerShp = std::shared_ptr<IRequestStreamHandler>;


#include <iostream>
#include <vector>
#include <functional>

namespace Json
{
  class JsonRequestStreamHandler : public IRequestStreamHandler
  {
  public:
    using OnBaseRequestsHandledCb = std::function<void()>;

    JsonRequestStreamHandler(std::istream& in,
      std::ostream& out,
      IRequestStreamParserShp parser,
      IRequestExecutorShp executor,
      IResponseStreamFormatterShp formatter);

    void Handle() override;

    void AddOnBaseRequestsHandledCb(OnBaseRequestsHandledCb cb);
    void OnBaseRequestsParsed();


  private:
    void OnBaseRequestsHandled();

  private:
    std::istream* _in;
    std::ostream* _out;
    IRequestStreamParserShp _parser;
    IRequestExecutorShp _executor;
    IResponseStreamFormatterShp _formatter;

    std::vector<OnBaseRequestsHandledCb> _onBaseRequestsHandledCbs;
    bool _isBaseRequestsParsed;
  };
  using JsonRequestStreamHandlerShp = std::shared_ptr<JsonRequestStreamHandler>;
  using JsonRequestStreamHandlerWkp = std::weak_ptr<JsonRequestStreamHandler>;
}



using namespace std;
using namespace Json;

JsonRequestStreamHandler::JsonRequestStreamHandler(
  std::istream& in,
  std::ostream& out,
  IRequestStreamParserShp parser,
  IRequestExecutorShp executor,
  IResponseStreamFormatterShp formatter) :
  _in(&in),
  _out(&out),
  _parser(std::move(parser)),
  _executor(std::move(executor)),
  _formatter(std::move(formatter)),
  _onBaseRequestsHandledCbs(),
  _isBaseRequestsParsed(false)
{}

void JsonRequestStreamHandler::Handle()
{
  _parser->SetRequestStream(*_in);
  _formatter->Start(*_out);
  while (_parser->HasRequest())
  {
    auto request = _parser->GetNextRequest();
    auto response = _executor->Execute(request.get());
    if (response)
    {
      _formatter->Format(*response);
    }

    if (_isBaseRequestsParsed)
    {
      OnBaseRequestsHandled();
      _isBaseRequestsParsed = false;
    }
  }
  _formatter->Finish();
}

void Json::JsonRequestStreamHandler::AddOnBaseRequestsHandledCb(OnBaseRequestsHandledCb cb)
{
  _onBaseRequestsHandledCbs.push_back(cb);
}

void Json::JsonRequestStreamHandler::OnBaseRequestsParsed()
{
  _isBaseRequestsParsed = true;
}

void Json::JsonRequestStreamHandler::OnBaseRequestsHandled()
{
  for (const auto& cb : _onBaseRequestsHandledCbs)
    cb();
}


#include <memory>

class IRequestStreamHandlerBuilder
{
public:
  virtual ~IRequestStreamHandlerBuilder() = default;

  virtual IRequestStreamHandlerShp Build() = 0;

protected:
  virtual IRequestStreamParserShp BuildRequestStreamParser() = 0;
  virtual IRequestExecutorShp BuildRequestExecutor() = 0;
  virtual IResponseStreamFormatterShp BuildResponseStreamFormatter() = 0;
};
using IRequestStreamHandlerBuilderShp = std::shared_ptr<IRequestStreamHandlerBuilder>;


#include <iostream>
#include <vector>

namespace Json
{
  class IRequestParser;
  using IRequestParserShp = std::shared_ptr<IRequestParser>;
  class IResponseFormatter;
  using IResponseFormatterShp = std::shared_ptr<IResponseFormatter>;
  class RequestStreamParser;
  using RequestStreamParserShp = std::shared_ptr<RequestStreamParser>;
}

class ISpecificRequestExecutor;
using ISpecificRequestExecutorShp = std::shared_ptr<ISpecificRequestExecutor>;
class Database;
using DatabaseShp = std::shared_ptr<Database>;
class PathSearcher;
using PathSearcherShp = std::shared_ptr<PathSearcher>;

namespace Json
{
  class RequestStreamHandlerBuilder : public IRequestStreamHandlerBuilder
  {
  public:
    RequestStreamHandlerBuilder(std::istream& in,
      std::ostream& out,
      DatabaseShp db);
    IRequestStreamHandlerShp Build() override;

  protected:
    IRequestStreamParserShp BuildRequestStreamParser() override;
    IRequestExecutorShp BuildRequestExecutor() override;
    IResponseStreamFormatterShp BuildResponseStreamFormatter() override;

    std::vector<Json::IRequestParserShp> BuildJsonInputRequestParsers();
    std::vector<Json::IRequestParserShp> BuildJsonOutputRequestParsers();

    std::vector<ISpecificRequestExecutorShp> BuildSpecificRequestExecutors();

    std::vector<Json::IResponseFormatterShp> BuildSpecificResponseFormatters();

    RequestStreamParserShp BuildJsonRequestStreamParser();

  protected:
    std::istream& _in;
    std::ostream& _out;
    DatabaseShp _db;
    PathSearcherShp _pathSearcher;
  };
  using JsonRequestStreamHandlerBuilderShp = std::shared_ptr<RequestStreamHandlerBuilder>;
}










using namespace std;
using namespace Json;

RequestStreamHandlerBuilder::RequestStreamHandlerBuilder(
  std::istream& in,
  std::ostream& out,
  DatabaseShp db) :
  _in(in),
  _out(out),
  _db(std::move(db)),
  _pathSearcher(std::make_shared<PathSearcher>())
{
}

IRequestStreamHandlerShp RequestStreamHandlerBuilder::Build()
{
  auto parser = BuildJsonRequestStreamParser();

  auto requestStreamHandler = std::make_shared<JsonRequestStreamHandler>(
    _in,
    _out,
   parser,
    BuildRequestExecutor(),
    BuildResponseStreamFormatter());

  
  parser->AddOnBaseRequestsParsedCb([handler = JsonRequestStreamHandlerWkp(requestStreamHandler)]()
    {
      if (handler.expired())
        return;
      auto handlerShp = handler.lock();
      handlerShp->OnBaseRequestsParsed();
    });

  requestStreamHandler->AddOnBaseRequestsHandledCb([pathSearcher = PathSearcherWkp(_pathSearcher), db = this->_db]()
    {
      if (pathSearcher.expired())
        return;
      auto pathSearcherShp = pathSearcher.lock();
      pathSearcherShp->Initialize(*db, db->GetRoutingSettings());
    });

  return requestStreamHandler;
}

IRequestStreamParserShp RequestStreamHandlerBuilder::BuildRequestStreamParser()
{
  return BuildJsonRequestStreamParser();
}

IRequestExecutorShp RequestStreamHandlerBuilder::BuildRequestExecutor()
{
  auto executor = std::make_shared<RequestStreamExecutor>();
  auto specificExecutors = BuildSpecificRequestExecutors();
  for (auto& i : specificExecutors)
    executor->RegisterExecutor(std::move(i));
  return executor;
}

IResponseStreamFormatterShp RequestStreamHandlerBuilder::BuildResponseStreamFormatter()
{
  auto formatter = std::make_shared<ResponseStreamFormatter>();
  auto specificFormatters = BuildSpecificResponseFormatters();
  for (auto& i : specificFormatters)
    formatter->RegisterResponseFormatter(std::move(i));
  return formatter;
}

std::vector<IRequestParserShp> RequestStreamHandlerBuilder::BuildJsonInputRequestParsers()
{
  return {
  std::make_shared<InputBusRequestParser>(),
  std::make_shared<InputStopRequestParser>(),
  };
}

std::vector<IRequestParserShp> RequestStreamHandlerBuilder::BuildJsonOutputRequestParsers()
{
  return {
    std::make_shared<OutputBusRequestParser>(),
    std::make_shared<OutputStopRequestParser>(),
    std::make_shared<FindRouteRequestParser>(),
  };
}

std::vector<ISpecificRequestExecutorShp> RequestStreamHandlerBuilder::BuildSpecificRequestExecutors()
{
  return {
    std::make_shared<OutputBusRequestExecutor>(_db),
    std::make_shared<OutputStopRequestExecutor>(_db),
    std::make_shared<InputBusRequestExecutor>(_db),
    std::make_shared<InputStopRequestExecutor>(_db),
    std::make_shared<RoutingSettingsRequestExecutor>(_db),
    std::make_shared<FindRouteRequestExecutor>(_db, _pathSearcher),
  };
}

std::vector<Json::IResponseFormatterShp> RequestStreamHandlerBuilder::BuildSpecificResponseFormatters()
{
  return {
  std::make_shared<InputBusResponseFormatter>(),
  std::make_shared<InputStopResponseFormatter>(),
  std::make_shared<OutputBusResponseFormatter>(),
  std::make_shared<OutputStopResponseFormatter>(),
  std::make_shared<FindRouteResponseFormatter>()
  };
}

RequestStreamParserShp Json::RequestStreamHandlerBuilder::BuildJsonRequestStreamParser()
{
  auto parser = std::make_shared<RequestStreamParser>();
  
  parser->RegisterRoutingSettingsParser(std::make_shared<InputRoutingSettingsParser>());

  auto specificOutputParsers = BuildJsonOutputRequestParsers();
  for (auto& p : specificOutputParsers)
  {
    parser->RegisterOutputRequestsParser(std::move(p));
  }

  auto specificInputParsers = BuildJsonInputRequestParsers();
  for (auto& p : specificInputParsers)
  {
    parser->RegisterInputRequestsParser(std::move(p));
  }

  return parser;
}

#include <iostream>
#include <fstream>

//#define DEBUG
//#define Line
#define JsonCfg

using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

#ifndef DEBUG
  auto db = make_shared<Database>();

#ifdef Line
  LineRequestStreamHandlerBuilder requestHandlerBuilder(cin, cout, db);
#endif

#ifdef JsonCfg

  /*string outFileName = "Output.txt";
  ofstream out(outFileName, std::ios_base::out | std::ios_base::trunc);
  if (!out.is_open())
  {
    cerr << outFileName << " doesn't open!";
    return -1;
  }


  string inFileName = "Input.txt";
  fstream in(inFileName, std::ios_base::in);
  if (!in.is_open())
  {
    cerr << inFileName << " doesn't open!";
    return -1;
  }

  Json::RequestStreamHandlerBuilder requestHandlerBuilder(in, out, db);*/
    Json::RequestStreamHandlerBuilder requestHandlerBuilder(cin, cout, db);
#endif

  auto requestHandler = requestHandlerBuilder.Build();
  requestHandler->Handle();

#else
  TestModule testModule;
  testModule.Run();
#endif // !DEBUG

  


  return 0;
}
