#version 460
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoord;
uniform mat4 model;
uniform vec2 mover;

out vec2 texcoords;

void main()
{
	gl_Position = model * vec4(aPos.x + mover.x,mover.y + aPos.y, 0.0 , 1.0);
	texcoords = aTexCoord;
}