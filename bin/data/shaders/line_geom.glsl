#version 150

layout(lines_adjacency) in;
// layout(lines) in;
layout(triangle_strip, max_vertices = 6) out;
// layout(line_strip, max_vertices = 2) out;

uniform mat4 modelViewProjectionMatrix;

void main(){
	float width = 30.0;
	float halfWidth = width / 2.0;

	vec3 rightVector = vec3(0.0, 0.0, 1.0);

	vec3 v0 = gl_in[0].gl_Position.xyz;
	vec3 v1 = gl_in[1].gl_Position.xyz;
	vec3 v2 = gl_in[2].gl_Position.xyz;
	vec3 v3 = gl_in[3].gl_Position.xyz;

	vec3 v01 = normalize(v0 - v1);
	vec3 v21 = normalize(v2 - v1);
	
	vec3 tangent = normalize(v21 - v01);

	vec3 normal = normalize(cross(tangent, rightVector));

	gl_Position = modelViewProjectionMatrix * vec4(v1 - normal * halfWidth, 1.0);
	EmitVertex();

	gl_Position = modelViewProjectionMatrix * vec4(v1 + normal * halfWidth, 1.0);
	EmitVertex();

	gl_Position = modelViewProjectionMatrix * vec4(v2 + normal * halfWidth, 1.0);
	EmitVertex();

	EndPrimitive();

	gl_Position = modelViewProjectionMatrix * vec4(v2 + normal * halfWidth, 1.0);
	EmitVertex();

	gl_Position = modelViewProjectionMatrix * vec4(v2 - normal * halfWidth, 1.0);
	EmitVertex();

	gl_Position = modelViewProjectionMatrix * vec4(v1 - normal * halfWidth, 1.0);
	EmitVertex();

	EndPrimitive();

	// gl_Position = modelViewProjectionMatrix * vec4(v1, 1.0);
	// EmitVertex();

	// gl_Position = modelViewProjectionMatrix * vec4(v2, 1.0);
	// EmitVertex();

	// EndPrimitive();
}