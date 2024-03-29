#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 ModelMatrix;
out vec2 UV;

void main()
{
	gl_Position = ModelMatrix * vec4(aPos, 1.0);
	UV = aTexCoord;
}