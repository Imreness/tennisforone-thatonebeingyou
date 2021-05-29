#version 460
in vec2 texcoords;
out vec4 fragcolor;

uniform sampler2D tex;

void main()
{
	vec4 color = texture(tex, texcoords);
	if(color.a == 0)
	{
		discard;
	}
	else
	{
		fragcolor = color;
	}
}