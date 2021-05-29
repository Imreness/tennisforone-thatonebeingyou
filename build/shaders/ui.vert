#version 460
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoord;
uniform mat4 model;

out vec2 texcoords;

void main()
{
	gl_Position = vec4(aPos, 0.0 , 1.0);
	texcoords = aTexCoord;
}