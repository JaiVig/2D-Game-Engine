#include<SDL.h>
#include<gl/glew.h>
#include"Crusty.h"
namespace Crusty {
	int init()
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		return 0;
	}
}