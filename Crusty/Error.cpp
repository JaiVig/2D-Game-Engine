#include"Error.h"
#include<iostream>
#include<SDL.h>
#include<cstdlib>
namespace Crusty {
	void fatalError(std::string error) {
		std::cout << error << std::endl;
		std::cout << "enter a no. to quit";
		int a;
		std::cin >> a;
		SDL_Quit;
		exit(10);
	}
}