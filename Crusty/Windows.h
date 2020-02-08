#pragma once
#include"SDL.h"
#include"GL/glew.h"
#include<string>
namespace Crusty {
	enum  WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BODERLESS = 0x4 };
	class Windows
	{
	public:
		Windows();
		~Windows();
		int create(std::string windowName, int screenwidth, int screenheight, unsigned int currentFlags);
		void swapBuffers();
		int getScreenWidth() { _screenWidth; }
		int getScreenHeight() { _screenHeight; }

	private:
		SDL_Window* _window;
		int _screenWidth;
		int _screenHeight;
	};

}