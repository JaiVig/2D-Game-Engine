#include "ImageLoader.h"
#include"picoPNG.h"
#include"IOManager.h"
#include"Error.h"
#include<iostream>
namespace Crusty {
	GLTexture ImageLoader::loadTexture(std::string filepath)
	{
		GLTexture texture = {}; //initialized everything to 0 in the struct
		std::vector<unsigned char> outputBuffer;
		std::vector<unsigned char> inputImage;
		unsigned long width, height;
		if (IOManager::ReadFileToBuffer(filepath, inputImage) == false)
		{
			fatalError("Failed to load png file to buffer!");
		}
		int err = decodePNG(outputBuffer, width, height, &inputImage[0], inputImage.size(), true);

		if (err != 0)
		{

			fatalError("decodePNG failed " + std::to_string(err));
		}
		glGenTextures(1, &(texture.id));
		glBindTexture(GL_TEXTURE_2D, texture.id);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(outputBuffer[0]));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		texture.height = height;
		texture.width = width;
		return texture;
	}
}