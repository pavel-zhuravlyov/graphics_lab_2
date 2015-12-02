#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec3 normal;
layout (location = 4) in mat4 modelMatrix;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 normal0;
out vec3 color0;

void main()
{
	mat4 modelViewMatrix = viewMatrix * modelMatrix;
	gl_Position = projectionMatrix * (modelViewMatrix * vec4(position, 1.0));
	normal0 = (modelViewMatrix * vec4(normal, 1.0)).xyz;
	color0 = color;
}	