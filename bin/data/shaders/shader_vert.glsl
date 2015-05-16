#version 150

uniform mat4 modelViewProjectionMatrix;

in vec4 position;
in vec4 normal;

out vec3 varyingNormal;

void main(){
	gl_Position = modelViewProjectionMatrix * position; 

	varyingNormal = normal.xyz;
}