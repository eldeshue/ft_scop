
#version 330 core

in vec3 verColor;
in vec2 texCoord;

out vec4 FragColor;

void main()
{
	FragColor = vec4(verColor, 1.0f);
}
