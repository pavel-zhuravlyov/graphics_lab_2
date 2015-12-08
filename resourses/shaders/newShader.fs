#version 430 core

in vec2 TexCoord;
in vec3 Color;
in vec3 Normal;

uniform sampler2D Sampler;

uniform vec3 Ambient;
uniform vec3 LightDirection;
uniform vec3 HalfVector;
uniform float Shininess;
uniform float Strength;

layout (location = 0) out vec4 color;

void main()
{
	color = texture2D(Sampler, TexCoord) * vec4(Color, 1.0);
}

