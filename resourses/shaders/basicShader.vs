#version 120

attribute vec3 position;
attribute vec3 color;
attribute vec2 texCoord;
attribute vec3 normal;
attribute mat4 modelMatrix;

varying vec2 texCoord0;
varying vec3 normal0;
varying vec3 color0;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;


void main()
{
	gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4(position, 1.0);
	gl_Color = vec4(color, 1.0);
	
	texCoord0 = texCoord;
	normal0 = ((viewMatrix * modelMatrix) * vec4(normal, 0.0)).xyz;
}
