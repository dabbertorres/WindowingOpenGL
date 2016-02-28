#version 330 core

uniform mat4 matrix;

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;

out vec4 fragColor;

void main()
{
	gl_Position = position * matrix;
	fragColor = color;
}