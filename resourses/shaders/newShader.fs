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
	//vec3 LightColor = vec3(1.0, 1.0, 1.0);

	//float diffuse = max(0.0, dot(Normal, LightDirection));
	//float specular = max(0.0, dot(Normal, HalfVector));

	//if (diffuse == 0.0) {
	//	specular = 0.0;
	//}
	//else {
	//	specular = pow(specular, Shininess);
	//}

	//vec3 scatteredLight = Ambient + LightColor * diffuse;
	//vec3 reflectedLight = LightColor * specular * Strength;

	//color = texture2D(Sampler, TexCoord) * vec4( min(Color * scatteredLight + reflectedLight, vec3(1.0)), 1.0);
	color = vec4(Color, 1.0);
}

