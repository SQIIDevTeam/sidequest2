#include "Config.h"
#include <fstream>
#include <sstream>
#include <iostream>

<<<<<<< HEAD
=======
/** read the config file */
>>>>>>> c6ea8a111ee6b09ee0d63ea0a27a942949897cef
Config::Config(std::string filename)
/** read the config file */{
	std::ifstream file(filename, std::ios::in);
<<<<<<< HEAD
	if (file == 0)
	//Exit if no file found  
	{
		std::cout << "No file found: " << filename << "\n"; 
		return;
=======
	if (!file)
	{
		std::cerr << "Could not load config file: " << filename << '\n';
		throw std::runtime_error(std::string("Config::(constructor): Could not load config file ") + filename);
>>>>>>> c6ea8a111ee6b09ee0d63ea0a27a942949897cef
	}
	while (!file.eof())
	{
		std::string line;
		std::getline(file, line);

		if (line.size() >= 2 && line[0] != '/' && line[1] != '/')
		{

			auto index = line.find('=');
			if (index == line.size() - 1)
				continue;

			m_config.insert(std::make_pair(std::string(line.begin(), line.begin() + (index)), std::string(line.begin() + (index + 1), line.end())));
		}
	}
}


