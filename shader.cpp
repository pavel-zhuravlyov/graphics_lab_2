#include "shader.h"
#include <iostream>
#include <fstream>

ShaderProgram::ShaderProgram(const std::string& fileName)
{
	program = glCreateProgram();
	shaders[0] = createShader(loadShader(fileName + ".vs"), GL_VERTEX_SHADER);
	shaders[1] = createShader(loadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

	for(unsigned int i = 0; i < NUM_SHADERS; i++)
		glAttachShader(program, shaders[i]);

	glBindAttribLocation(program, 0, "position");
    glBindAttribLocation(program, 1, "color");
	glBindAttribLocation(program, 2, "texCoord");
	glBindAttribLocation(program, 3, "normal");
    glBindAttribLocation(program, 4, "modelMatrix");

	glLinkProgram(program);
	checkShaderError(program, GL_LINK_STATUS, true, "Error linking shader program");

	glValidateProgram(program);
	checkShaderError(program, GL_LINK_STATUS, true, "Invalid shader program");

    uniforms[0] = glGetUniformLocation(program, "globalModelMatrix");
	uniforms[1] = glGetUniformLocation(program, "viewMatrix");
    uniforms[2] = glGetUniformLocation(program, "projectionMatrix");
}

ShaderProgram::~ShaderProgram()
{
	for(unsigned int i = 0; i < NUM_SHADERS; i++)
    {
        glDetachShader(program, shaders[i]);
        glDeleteShader(shaders[i]);
    }

	glDeleteProgram(program);
}

void ShaderProgram::bind()
{
	glUseProgram(program);
}

void ShaderProgram::update(const glm::mat4 globalModelMatrix, const glm::mat4 viewMatrix, const glm::mat4 projectionMatrix)
{
    glUniformMatrix4fv(uniforms[0], 1, GL_FALSE, &globalModelMatrix[0][0]);
	glUniformMatrix4fv(uniforms[1], 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(uniforms[2], 1, GL_FALSE, &projectionMatrix[0][0]);
}

std::string ShaderProgram::loadShader(const std::string& fileName)
{
    std::ifstream file;
    file.open((fileName).c_str());

    std::string output;
    std::string line;

    if(file.is_open())
    {
        while(file.good())
        {
            getline(file, line);
			output.append(line + "\n");
        }
    }
    else
    {
		std::cerr << "Unable to load shader: " << fileName << std::endl;
    }

    return output;
}

void ShaderProgram::checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
    GLint success = 0;
    GLchar error[1024] = { 0 };

    if(isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);

    if(success == GL_FALSE)
    {
        if(isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);

        std::cerr << errorMessage << ": '" << error << "'" << std::endl;
    }
}

GLuint ShaderProgram::createShader(const std::string& text, unsigned int type)
{
    GLuint shader = glCreateShader(type);

    if(shader == 0)
		std::cerr << "Error compiling shader type " << type << std::endl;

    const GLchar* p[1];
    p[0] = text.c_str();
    GLint lengths[1];
    lengths[0] = text.length();

    glShaderSource(shader, 1, p, lengths);
    glCompileShader(shader);

    checkShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!");

    return shader;
}
