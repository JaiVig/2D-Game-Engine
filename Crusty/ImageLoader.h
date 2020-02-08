#pragma once
#include<GL/glew.h>
#include<string>
#include"GLTexture.h"
namespace Crusty {
	class ImageLoader
	{
	public:
		static GLTexture loadTexture(std::string filepath);
	};

}