#include "TextureCache.h"
#include"ImageLoader.h"
#include<iostream>
namespace Crusty {
	TextureCache::TextureCache()
	{
	}


	TextureCache::~TextureCache()
	{
	}

	GLTexture TextureCache::getTexture(std::string texturePath)
	{
		auto mapIterator = _textureMap.find(texturePath);

		if (mapIterator == _textureMap.end())
		{
			GLTexture newTexture = ImageLoader::loadTexture(texturePath);

			_textureMap.insert(std::make_pair(texturePath, newTexture));

			return newTexture;
		}

		return mapIterator->second;
	}
}