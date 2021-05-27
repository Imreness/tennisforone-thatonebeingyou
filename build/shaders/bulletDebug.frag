#version 420
out vec4 fragcolor;

uniform vec3 color;

void main()
{
	fragcolor = vec4(color, 1.);
}