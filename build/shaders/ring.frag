#version 460
in vec2 texcoords;
in float horizontalDistanceFromCenter;
in float verticalDistanceFromCenter;
out vec4 fragcolor;

uniform sampler2D tex;

void main()
{
	vec4 color = texture(tex, texcoords);
	if(color.a == 0)
	{
		discard;
	}
	else if(horizontalDistanceFromCenter > 2)
	{
		discard;
	}
	else if(verticalDistanceFromCenter > 1.8){
		discard;
	}
	else
	{
		fragcolor = color;
	}
}