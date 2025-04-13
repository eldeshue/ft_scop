
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;
layout (location = 2) in vec2 tPos;
out vec3 verColor;
out vec2 texCoord;

uniform mat4 mvp;

void main()
{
   gl_Position = mvp * vec4(aPos, 1);
   verColor = aCol;
   texCoord = tPos;
}
