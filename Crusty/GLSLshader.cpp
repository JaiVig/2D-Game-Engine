#include "GLSLshader.h"
#include"Error.h"
#include<fstream>
#include<vector>
#include<iostream>
namespace Crusty {
	GLSLshader::GLSLshader()
	{
		_progID = 0;
		_vertID = 0;
		_fragID = 0;
		_numAttributes = 0;
	}


	GLSLshader::~GLSLshader()
	{
	}

	void GLSLshader::compileShaders(const std::string &vertPath, const std::string &fragPath)
	{
		_vertID = glCreateShader(GL_VERTEX_SHADER);
		if (_vertID == 0)
		{
			fatalError("Vertex shader failed to init");
		}

		_fragID = glCreateShader(GL_FRAGMENT_SHADER);
		if (_fragID == 0)
		{
			fatalError("frag shader failed to init");
		}
		// Vertex and fragment shaders are successfully compiled.
	// Now time to link them together into a _progID.
	// Get a _progID object.

		_progID = glCreateProgram();
		compileShader(vertPath, _vertID);
		compileShader(fragPath, _fragID);

	}



	void GLSLshader::compileShader(const std::string &filepath, GLuint id)
	{
		std::ifstream shaderStream(filepath);
		if (shaderStream.fail())
		{
			perror(filepath.c_str());
			fatalError("could not load :: " + filepath);
		}

		std::string fileContents = "";
		std::string line;
		while (std::getline(shaderStream, line))
		{
			fileContents += line + "\n";
		}
		shaderStream.close();


		const char *contentsPtr = fileContents.c_str();
		glShaderSource(id, 1, &contentsPtr, nullptr);

		glCompileShader(id);

		GLint success = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

			// Provide the infolog in whatever manor you deem best.
			// Exit with failure.
			glDeleteShader(id); // Don't leak the shader.
			std::printf("%s\n", &errorLog[0]);
			fatalError("shader " + filepath + " failed to compile");
		}
	}

	void GLSLshader::addAttr(const std::string& attribName)
	{

		glBindAttribLocation(_progID, _numAttributes, attribName.c_str());
		_numAttributes++;

	}

	GLint GLSLshader::getUniformLocation(const std::string& uniformName)
	{
		GLint locID = glGetUniformLocation(_progID, uniformName.c_str());
		if (locID == GL_INVALID_INDEX)
		{
			fatalError("uniform " + uniformName + " not found in frag");
		}
		return locID;
	}

	void GLSLshader::linkShaders()
	{


		// Attach our shaders to our _progID
		glAttachShader(_progID, _vertID);
		glAttachShader(_progID, _fragID);

		// Link our _progID
		glLinkProgram(_progID);
		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(_progID, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(_progID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> errorLog(maxLength);
			glGetProgramInfoLog(_progID, maxLength, &maxLength, &errorLog[0]);

			// We don't need the _progID anymore.
			glDeleteProgram(_progID);
			// Don't leak shaders either.
			glDeleteShader(_vertID);
			glDeleteShader(_fragID);
			std::printf("%s\n", &errorLog[0]);
			fatalError("shaders failed to link");
		}

		// Always detach shaders after a successful link.
		glDetachShader(_progID, _vertID);
		glDetachShader(_progID, _fragID);
		glDeleteShader(_vertID);
		glDeleteShader(_fragID);
	}
	void GLSLshader::use()
	{
		glUseProgram(_progID);
		for (int i = 0; i < _numAttributes; i++)
		{
			glEnableVertexAttribArray(i);
		}
	}

	void GLSLshader::unuse()
	{
		glUseProgram(0);
		for (int i = 0; i < _numAttributes; i++)
		{
			glDisableVertexAttribArray(i);
		}
	}
}