#pragma once

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

