#version 150

uniform vec4 globalColor;

in vec3 varyingNormal;

out vec4 color;

void main(){
	color = globalColor;
}