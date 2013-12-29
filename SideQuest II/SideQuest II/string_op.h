#include <string>
#include <sstream>

template <typename T>
std::string toString(T in)
{
	std::stringstream s;
	s << in;
	return s.str();
}

template <typename T>
T stringTo(std::string str)
{
	std::stringstream s(str);
	T val;
	s >> val;
	return val;
}