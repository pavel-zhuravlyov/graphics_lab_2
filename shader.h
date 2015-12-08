#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>
#include "transform.h"

class ShaderProgram
{
public:
	ShaderProgram(const std::string& fileName);

	void bind();
	void update(const glm::mat4 globalModelMatrix, const glm::mat4 viewMatrix, const glm::mat4 projectionMatrix,
                            glm::vec3 ambient, glm::vec3 lightDirection, glm::vec3 halfVector,float shininess, float strength);

	~ShaderProgram();

private:
	static const unsigned int NUM_SHADERS = 2;
	static const unsigned int NUM_UNIFORMS = 8;

	std::string loadShader(const std::string& fileName);
	void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint createShader(const std::string& text, unsigned int type);

	GLuint program;
	GLuint shaders[NUM_SHADERS];
	GLuint uniforms[NUM_UNIFORMS];
};

#endif
