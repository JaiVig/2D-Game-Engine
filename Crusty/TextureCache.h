#pragma once
#include<map>
#include<sstream>
#include"GLTexture.h"
namespace Crusty {
	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();
		GLTexture getTexture(std::string texturePath);
	private:
		std::map<std::string, GLTexture> _textureMap;
	};

}