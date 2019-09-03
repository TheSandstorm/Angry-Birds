#include "ShaderLoader.h" 
#include<iostream>
#include<fstream>
#include<vector>
#include <map>

ShaderLoader::ShaderLoader(void) {}
ShaderLoader::~ShaderLoader(void) {}

std::map<std::string, GLuint> shaderMap;
std::map<std::string, GLuint> programMap;

GLuint ShaderLoader::CreateProgram(const char* vertexShaderFilename, const char* fragmentShaderFilename)
{
	std::string programFilename = vertexShaderFilename + *fragmentShaderFilename;
	std::map<std::string, GLuint>::iterator it = shaderMap.find(vertexShaderFilename);
	if (it != shaderMap.end())
	{
		return (*it).second; // pair.second
		// same as:
		//return shaderMap[shaderName];
	}
	else
	{
		GLuint vertexShaderID = CreateShader(GL_VERTEX_SHADER, vertexShaderFilename);
		GLuint fragmentShaderID = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderFilename);
		GLuint program = glCreateProgram();
		glAttachShader(program, vertexShaderID);
		glAttachShader(program, fragmentShaderID);
		glLinkProgram(program);

		// Check for link errors
		int link_result = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &link_result);
		if (link_result == GL_FALSE)
		{
			std::string programName = vertexShaderFilename + *fragmentShaderFilename;
			PrintErrorDetails(false, program, programName.c_str());
			return 0;
		}
		programMap.insert({ vertexShaderFilename, program });
		return program;
	}
}

GLuint ShaderLoader::CreateShader(GLenum shaderType, const char* shaderName)
{
	// 1. search map for file name
	// 2. if it exists in the map, return map[fileName]
	// 3. if not, make the shader as normal
	// 4. add newly created shader to map with the key fileName

	std::map<std::string, GLuint>::iterator it = shaderMap.find(shaderName);
	if (it != shaderMap.end()) // if the shader filename was found
	{
		return (*it).second; // pair.second
		// same as:
		//return shaderMap[shaderName];
	}
	else
	{
		std::string shaderSource = ReadShaderFile(shaderName);
		GLuint shaderID = glCreateShader(shaderType);
		const char *shader_code_ptr = shaderSource.c_str();
		const int shader_code_size = shaderSource.size();
		glShaderSource(shaderID, 1, &shader_code_ptr, &shader_code_size);
		glCompileShader(shaderID);

		// Check for errors
		int compile_result = 0;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compile_result);
		if (compile_result == GL_FALSE)
		{
			PrintErrorDetails(true, shaderID, shaderName);
			return 0;
		}
		shaderMap.insert({ shaderName, shaderID });
		return shaderID;
	}
}

std::string ShaderLoader::ReadShaderFile(const char *filename)
{
	// Open the file for reading
	std::ifstream file(filename, std::ios::in);
	std::string shaderCode;

	// Ensure the file is open and readable
	if (!file.good()) {
		std::cout << "Cannot read file:  " << filename << std::endl;
		return "";
	}

	// Determine the size of of the file in characters and resize the string variable to accomodate
	file.seekg(0, std::ios::end);
	shaderCode.resize((unsigned int)file.tellg());

	// Set the position of the next character to be read back to the beginning
	file.seekg(0, std::ios::beg);
	// Extract the contents of the file and store in the string variable
	file.read(&shaderCode[0], shaderCode.size());
	file.close();
	return shaderCode;
}

void ShaderLoader::PrintErrorDetails(bool isShader, GLuint id, const char* name)
{
	int infoLogLength = 0;
	// Retrieve the length of characters needed to contain the info log
	(isShader == true) ? glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength) : glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
	std::vector<char> log(infoLogLength);

	// Retrieve the log info and populate log variable
	(isShader == true) ? glGetShaderInfoLog(id, infoLogLength, NULL, &log[0]) : glGetProgramInfoLog(id, infoLogLength, NULL, &log[0]);
	std::cout << "Error compiling " << ((isShader == true) ? "shader" : "program") << ": " << name << std::endl;
	std::cout << &log[0] << std::endl;
}