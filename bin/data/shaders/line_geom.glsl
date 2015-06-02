#version 150

layout(lines_adjacency) in;
// layout(lines) in;
layout(triangle_strip, max_vertices = 6) out;
// layout(line_strip, max_vertices = 2) out;

uniform mat4 modelViewProjectionMatrix;

uniform float lineWidth;

// Returns -1.0 if x < 0.0, else returns 1.0
float signPlus(float x){
	float s = step(0.0, x) * 2.0 - 1.0; 
	return s;
}

void main(){
	float halfWidth = lineWidth / 2.0;

	vec3 rightVector = vec3(0.0, 0.0, 1.0);

	vec3 v0 = gl_in[0].gl_Position.xyz;
	vec3 v1 = gl_in[1].gl_Position.xyz;
	vec3 v2 = gl_in[2].gl_Position.xyz;
	vec3 v3 = gl_in[3].gl_Position.xyz;

	vec3 v01 = normalize(v0 - v1);
	vec3 v21 = normalize(v2 - v1);
	vec3 v12 = -v21;
	vec3 v32 = normalize(v3 - v2);

	vec3 t1 = normalize(v21 - v01);
	vec3 t2 = normalize(v32 - v12);

	vec3 n1 = normalize(cross(t1, rightVector));
	// vec3 n1 = signPlus(dot(v01, v21)) * normalize(cross(t1, rightVector));
	vec3 n2 = normalize(cross(t2, rightVector));
	// vec3 n2 = signPlus(dot(v12, v32)) * normalize(cross(t2, rightVector));

	vec3 c1 = cross(n1, v01);
	float l1 = halfWidth / dot(c1, vec3(1.0, 1.0, 1.0));
	vec3 c2 = cross(n2, v32);
	float l2 = halfWidth / dot(c2, vec3(1.0, 1.0, 1.0));

	gl_Position = modelViewProjectionMatrix * vec4(v1 - n1 * l1, 1.0);
	EmitVertex();

	gl_Position = modelViewProjectionMatrix * vec4(v1 + n1 * l1, 1.0);
	EmitVertex();

	gl_Position = modelViewProjectionMatrix * vec4(v2 + n2 * l2, 1.0);
	EmitVertex();

	EndPrimitive();

	gl_Position = modelViewProjectionMatrix * vec4(v2 + n2 * l2, 1.0);
	EmitVertex();

	gl_Position = modelViewProjectionMatrix * vec4(v2 - n2 * l2, 1.0);
	EmitVertex();

	gl_Position = modelViewProjectionMatrix * vec4(v1 - n1 * l1, 1.0);
	EmitVertex();

	EndPrimitive();

	// gl_Position = modelViewProjectionMatrix * vec4(v1, 1.0);
	// EmitVertex();

	// gl_Position = modelViewProjectionMatrix * vec4(v2, 1.0);
	// EmitVertex();

	// EndPrimitive();
}