#version 460
in vec2 texcoords;
out vec4 fragcolor;

uniform sampler2D tex;

uniform bool isLitUp;

void main()
{
	vec4 color = texture(tex, texcoords);
    if(isLitUp){
        color = color * 1.3;
		color.w = 1;
    }
    else{
        color = color * 0.3;
		color.w = 1;
    }
	if(color.a == 0)
	{
		discard;
	}
	else
	{
		fragcolor = color;
	}
}