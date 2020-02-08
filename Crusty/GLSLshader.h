#pragma once
#include<string>
#include<GL/glew.h>
namespace Crusty {
	class GLSLshader
	{
	public:
		GLSLshader();
		~GLSLshader();

		void compileShaders(const std::string &vertPath, const std::string &fragPath);
		void use();
		void unuse();
		void linkShaders();
		void compileShader(const std::string &filepath, GLuint id);
		void addAttr(const std::string& attribName);

		GLint getUniformLocation(const std::string& uniformName);

	private:
		int _numAttributes;
		GLuint _progID;
		GLuint _vertID;
		GLuint _fragID;
	};

}