#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec3 normal;
layout (location = 4) in mat4 modelMatrix;

uniform mat4 globalModelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec2 TexCoord;
out vec3 Color;
out vec3 Normal;

void main()
{
	mat4 modelViewMatrix = viewMatrix * (globalModelMatrix * modelMatrix);
	gl_Position = projectionMatrix * (modelViewMatrix * vec4(position, 1.0));

	TexCoord = texCoord;
	Color = color;
	Normal = normal;
}	