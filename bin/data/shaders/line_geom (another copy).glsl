#version 150

layout(lines_adjacency) in;
// layout(lines) in;
// layout(triangle_strip, max_vertices = 6) out;
// layout(line_strip, max_vertices = 2) out;
layout(line_strip, max_vertices = 6) out;

// in vec4 vs_normal[];
in vec4 varyingNormal[];

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

	// vec3 n1 = vs_normal[1].xyz;
	// vec3 n2 = vs_normal[2].xyz;
	vec3 n1 = varyingNormal[1].xyz;
	vec3 n2 = varyingNormal[2].xyz;

	// vec3 u = v2 - v1;
	vec3 u = v1 - v2;
	float lu = length(u);

	float norm1 = dot(cross(n1, u), vec3(0.0, 0.0, 1.0));
	float l1 = halfWidth * lu / norm1;

	// vec3 u2 = v3 - v2;
	float norm2 = dot(cross(n2, u), vec3(0.0, 0.0, 1.0));
	float l2 = halfWidth * lu / norm2;
	// vec3 n01 = vec3(v01.y, -v01.x, 0.0);
	// vec3 n12 = vec3(v12.y, -v12.x, 0.0);
	// vec3 n23 = vec3(v23.y, -v23.x, 0.0);
	// vec3 n01 = normal(v01);
	// vec3 n12 = normal(v12);
	// vec3 n23 = normal(v23);

	// n01 *= signPlus(dot(n01, vec3(0.0, 1.0, 0.0)));
	// n12 *= signPlus(dot(n12, vec3(0.0, 1.0, 0.0)));
	// n23 *= signPlus(dot(n23, vec3(0.0, 1.0, 0.0)));

	// float co1 = step(1.0, dot(v01, -v12));
	// float co2 = step(1.0, dot(v12, -v23));

	// vec3 n1 = normalize(n01 + n12);
	// vec3 n2 = normalize(n12 + n23); 

	// float l1 = halfWidth / dot(n01, n1);
	// float l2 = halfWidth / dot(n12, n2);

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

	// // gl_Position = modelViewProjectionMatrix * vec4(v1, 1.0);
	// gl_Position = modelViewProjectionMatrix * vec4(n1, 1.0);
	// EmitVertex();

	// // gl_Position = modelViewProjectionMatrix * vec4(v2, 1.0);
	// gl_Position = modelViewProjectionMatrix * vec4(n2, 1.0);
	// EmitVertex();

	// EndPrimitive();
}