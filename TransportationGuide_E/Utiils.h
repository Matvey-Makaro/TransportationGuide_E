#pragma once

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