#include <cstdlib>
#include <iostream>

#include "App.h"
#include "Config.h"

int main()
{
	std::cout << "[INFO] Starting SideQuest II...\n";

	try
	{
		Config c("config.txt");
		std::cout << "[INFO] Starting with window size " << c.get<int>("windowsize_x") << "x" << c.get<int>("windowsize_y");
		App app(c);
		app.run();
	}
	catch (std::exception& exc)
	{
		std::cerr << "Exception in game: " << exc.what() << '\n';
	}
	
	std::cin.get();
	return 0;
}