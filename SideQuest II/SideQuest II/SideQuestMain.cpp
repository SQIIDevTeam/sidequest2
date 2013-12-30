#include <cstdlib>
#include <iostream>

#include "App.h"
#include "Config.h"

int main()
{
	try
	{
		Config c("config.txt");
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