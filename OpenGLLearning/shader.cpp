#include "shader.h"

Shader::Shader(const GLchar * vertexPath, const GLchar * fragmentPath)
{
	const GLchar* vShaderCode = getShaderCode(vertexPath);
	const GLchar* fShaderCode = getShaderCode(fragmentPath);

	unsigned int vShader = compileShader(GL_VERTEX_SHADER, vShaderCode);
	unsigned int fShader = compileShader(GL_FRAGMENT_SHADER, fShaderCode);

	programID = glCreateProgram();
	glAttachShader(programID, vShader);
	glAttachShader(programID, fShader);
	glLinkProgram(programID);
	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(programID, 512, NULL, infoLog);
		cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
	}

	glDeleteShader(vShader);
	glDeleteShader(fShader);
	delete[] vShaderCode;
	delete[] fShaderCode;
}

Shader::~Shader()
{
}

void Shader::use()
{
	glUseProgram(programID);
}

unsigned int Shader::getProgramID()
{
	return programID;
}

void Shader::setUniform(const string & name, bool value) const
{
	glUniform1i(glGetUniformLocation(programID, name.c_str()), (int)value);
}

void Shader::setUniform(const string & name, int value) const
{
	glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}

void Shader::setUniform(const string & name, float value) const
{
	glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
}

void Shader::setUniform(const string & name, glm::vec3 value) const
{
	glUniform3fv(glGetUniformLocation(programID, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setUniform(const string & name, glm::mat4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

const GLchar * Shader::getShaderCode(const GLchar * shaderPath)
{
	string shaderCode;
	ifstream shaderFile;

	shaderFile.exceptions(ifstream::failbit | ifstream::badbit);

	try
	{
		shaderFile.open(shaderPath);

		stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();

		shaderFile.close();

		shaderCode = shaderStream.str();
	}
	catch (ifstream::failure e)
	{
		cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
	}

	unsigned int codeLength = shaderCode.length() + 1;
	char* code = new char[codeLength];
	strcpy_s(code, codeLength, shaderCode.c_str());
	return code;
}

unsigned int Shader::compileShader(GLenum type, const GLchar* shaderCode)
{
	unsigned int shader;

	shader = glCreateShader(type);
	glShaderSource(shader, 1, &shaderCode, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
	}

	return shader;
}
