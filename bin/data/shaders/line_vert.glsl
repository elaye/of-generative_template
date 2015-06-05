#version 150

in vec4 position;
in vec4 normal;

out vec3 varyingNormal;

void main(){
	gl_Position = position;
	varyingNormal = normal.xyz;
}