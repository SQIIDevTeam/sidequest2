#pragma once
#include <string>
#include <map>
#include <vector>

#include "string_op.h"
class Config
{
public:
	Config(std::string filename);

	template <typename T>
	T get(std::string key) const;

private:
	std::map<std::string, std::string> m_config;
};


template <typename T>
T Config::get(std::string key) const
{
	auto it = m_config.find(key);
	if (it == m_config.end()) return T();
	return stringTo<T>(it->second);
}
