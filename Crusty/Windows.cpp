#include "Windows.h"
#include"Error.h"
namespace Crusty {

	Windows::Windows()
	{
	}


	Windows::~Windows()
	{
	}

	int Windows::create(std::string windowName, int screenwidth, int screenheight, unsigned int currentFlags)
	{
		Uint32 flags = SDL_WINDOW_OPENGL;



		_window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenwidth, screenheight, SDL_WINDOW_OPENGL);

		if (_window == nullptr)
			fatalError("SDL window could not be created");

		SDL_GLContext glContext = SDL_GL_CreateContext(_window);

		if (glContext == nullptr)
			fatalError("could not create gl context");
		GLenum glInitError = glewInit();

		if (glInitError != GLEW_OK)
		{
			fatalError("could not init GL");
		}
		std::printf("*** Opengl Version = %s ***", glGetString(GL_VERSION));
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		SDL_GL_SetSwapInterval(1);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		return 0;
	}

	void Windows::swapBuffers()
	{
		SDL_GL_SwapWindow(_window);
	}
}