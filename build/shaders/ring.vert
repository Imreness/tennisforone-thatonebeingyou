#version 460
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

out vec2 texcoords;

out float horizontalDistanceFromCenter;
out float verticalDistanceFromCenter;

void main()
{
	vec4 finalpos = proj * view * model * vec4(aPos,1.0);
	gl_Position = finalpos;
	texcoords = aTexCoord;
	horizontalDistanceFromCenter = abs(finalpos.x);
	verticalDistanceFromCenter = finalpos.y;
}