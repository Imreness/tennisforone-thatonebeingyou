#version 460
out vec4 fragcolor;
in vec2 texcoords;

uniform sampler2D tex;

void main(){
    fragcolor = texture(tex, texcoords);
}