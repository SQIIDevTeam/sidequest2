#pragma once
#include <string>
#include <map>
#include <vector>

#include "string_op.h"

/**
This class handles config files. You can specify which file should be used with the first constructor parameter
*/
class Config
{
public:
	Config(std::string filename);

	template <typename T>
	T get(std::string key) const;

private:
	std::map<std::string, std::string> m_config;
};

/**
	A template function that gets you the value in a config file in the type you specify in the template argument. 
	Supported types are those who can be read in with the >> operator.	
*/
template <typename T>
T Config::get(std::string key) const
{
	auto it = m_config.find(key);
	if (it == m_config.end()) return T();
	return stringTo<T>(it->second);
}
