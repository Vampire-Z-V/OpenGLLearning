#ifndef SHADER_H
#define SHADER_H

#include <glad\glad.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class Shader
{
public:
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	~Shader();

	void use();
	unsigned int getProgramID();
	void setUniform(const string &name, bool value) const;
	void setUniform(const string &name, int value) const;
	void setUniform(const string &name, float value) const;
	void setUniform(const string &name, glm::vec3 value) const;
	void setUniform(const string &name, glm::mat4 value) const;

private:
	const GLchar* getShaderCode(const GLchar* shaderPath);
	unsigned int compileShader(GLenum type, const GLchar* shaderCode);

	unsigned int programID;
	int success;
	char infoLog[512];
};

#endif // !SHADER_H
