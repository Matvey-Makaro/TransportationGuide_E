#include <algorithm>
#include "Utiils.h"

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
