#pragma once
#include"GLTexture.h"
#include<GL/glew.h>
#include<string>
namespace Crusty {
	class Sprite
	{
	public:
		Sprite();
		~Sprite();

		void init(float x, float y, float height, float width, std::string texturePath);
		void draw();

	private:
		float _x;
		float _y;
		float _height;
		float _width;
		GLuint _vboID;
		GLTexture _texture;
	};

}