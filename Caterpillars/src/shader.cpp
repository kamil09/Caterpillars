#include "shader.hpp"


// void Shader::checkLastLines(std::string lancuch){
// 	int i=0;
// 	for(i=0;lancuch[i]!='\0';i++);
// 	std::cout << "i: " << i << " znak: " << lancuch[i] << std::endl;
// 	for(;lancuch[i-i]=='\n';i--){
// 		std::cout << "znaleziono spacje" << std::endl;
// 		lancuch[i-i]='\0';
// 	}
// }

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath){
	this->shaderCount=0;
	this->loadShader(vertexPath, fragmentPath);
}

void Shader::loadShader(const GLchar *vertexPath, const GLchar *fragmentPath){
	// 1. Retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensures ifstream objects can throw exceptions:
	vShaderFile.exceptions (std::ifstream::badbit);
	fShaderFile.exceptions (std::ifstream::badbit);
	try
	{
		// Open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// Read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();

		// std::cout << "Stream: " << vShaderStream.str() << std::endl;
		// Convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	// this->checkLastLines(vertexCode);
	// this->checkLastLines(fragmentCode);
	int vShaderCodeLength = vertexCode.length();
	vShaderCode = vertexCode.c_str();
	int fShaderCodeLength = vertexCode.length();
	fShaderCode = fragmentCode.c_str();

	// std::cout<< "tekst: "<< vShaderCode << std::endl;
//

	// 2. Compile shaders
	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];
	// Vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, &vShaderCodeLength);
	glCompileShader(vertex);
	// Print compile errors if any
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, &fShaderCodeLength);
	glCompileShader(fragment);
	// Print compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Shader Program
	// newShaderProgram = glCreateProgram();
	GLuint newShaderProgram = glCreateProgram();
	glAttachShader(newShaderProgram, vertex);
	glAttachShader(newShaderProgram, fragment);
	glLinkProgram(newShaderProgram);
	// Print linking errors if any
	glGetProgramiv(newShaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(newShaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
	glDeleteShader(fragment);

	this->shaderCount++;
	this->shaderProgram.push_back(newShaderProgram);

}

void Shader::useShaderProgram(int i){
    glUseProgram(this->shaderProgram[i]);
}
