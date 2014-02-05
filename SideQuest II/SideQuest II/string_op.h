#pragma once
#include <string>
#include <sstream>

template <typename T>
std::string toString(T in)
{
	std::stringstream s;
	s << std::boolalpha << in;
	return s.str();
}

template <typename T>
T stringTo(std::string str)
{
	std::stringstream s(str);
	T val;
	s >> std::boolalpha >> val;
	return val;
}