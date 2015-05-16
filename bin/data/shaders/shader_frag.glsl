#version 150

uniform vec4 globalColor;

uniform float time;
uniform vec2 res;

in vec3 varyingNormal;

out vec4 color;

void main(){
	color = globalColor;
}