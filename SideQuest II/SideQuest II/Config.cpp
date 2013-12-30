#include "Config.h"
#include <fstream>
#include <sstream>


Config::Config(std::string filename)
{
	std::ifstream file(filename, std::ios::in);
	while (!file.eof())
	{
		std::string line;
		std::getline(file, line);

		auto index = line.find('=');
		if (index == line.size() - 1)
			continue;

		 m_config.insert(std::make_pair(std::string(line.begin(), line.begin() + (index)), std::string(line.begin() + (index + 1), line.end())));
	}
}

