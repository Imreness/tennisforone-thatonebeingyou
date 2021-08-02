#version 460
out vec4 fragcolor;
in vec2 texcoords;

uniform sampler2D tex;
uniform float darkness;

void main(){
    fragcolor = texture(tex, texcoords) * vec4(darkness , darkness , darkness , 1.);
}