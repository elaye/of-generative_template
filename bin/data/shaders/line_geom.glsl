#version 150

layout(lines_adjacency) in;
// layout(lines) in;
// layout(triangle_strip, max_vertices = 6) out;
// layout(line_strip, max_vertices = 2) out;
layout(line_strip, max_vertices = 6) out;

uniform mat4 modelViewProjectionMatrix;

uniform float lineWidth;

// Returns -1.0 if x < 0.0, else returns 1.0
float signPlus(float x){
	float s = step(0.0, x) * 2.0 - 1.0; 
	return s;
}

vec3 normal(vec3 v){
	vec3 n = vec3(v.y, -v.x, v.z);
	// Keep the normal in the y > 0 plane
	// n *= signPlus(dot(n, vec3(0.0, 1.0, 0.0)));
	return n;
}

void main(){
	float halfWidth = lineWidth / 2.0;

	vec3 v0 = gl_in[0].gl_Position.xyz;
	vec3 v1 = gl_in[1].gl_Position.xyz;
	vec3 v2 = gl_in[2].gl_Position.xyz;
	vec3 v3 = gl_in[3].gl_Position.xyz;

	vec3 v01 = normalize(v0 - v1);
	vec3 v12 = normalize(v1 - v2);
	vec3 v23 = normalize(v2 - v3);

	vec3 n01 = normal(v01);
	vec3 n12 = normal(v12);
	vec3 n23 = normal(v23);


	vec3 d1 =  halfWidth * cross(v01, v12).z / (dot(v01, v12) - 1.0) * v01;
	vec3 n1 = halfWidth * n01 + d1;

	vec3 d2 =  halfWidth * cross(v12, v23).z / (dot(v12, v23) - 1.0) * v12;
	vec3 n2 = halfWidth * n12 + d2;

	// vec3 n1 = normalize(n01 + n12);
	// vec3 n2 = normalize(n12 + n23); 

	// float l1 = halfWidth / dot(n01, n1);
	// float l2 = halfWidth / dot(n12, n2);

	gl_Position = modelViewProjectionMatrix * vec4(v1 - n1, 1.0);
	EmitVertex();

	gl_Position = modelViewProjectionMatrix * vec4(v1 + n1, 1.0);
	EmitVertex();

	gl_Position = modelViewProjectionMatrix * vec4(v2 + n2, 1.0);
	EmitVertex();

	EndPrimitive();

	gl_Position = modelViewProjectionMatrix * vec4(v2 + n2, 1.0);
	EmitVertex();

	gl_Position = modelViewProjectionMatrix * vec4(v2 - n2, 1.0);
	EmitVertex();

	gl_Position = modelViewProjectionMatrix * vec4(v1 - n1, 1.0);
	EmitVertex();

	EndPrimitive();

	// gl_Position = modelViewProjectionMatrix * vec4(v1, 1.0);
	// EmitVertex();

	// gl_Position = modelViewProjectionMatrix * vec4(v2, 1.0);
	// EmitVertex();

	// EndPrimitive();
}