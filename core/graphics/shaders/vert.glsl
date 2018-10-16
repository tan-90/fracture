#version 400 core

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 tangent;
layout (location = 3) in vec3 bitangent;
layout (location = 4) in vec3 color;
layout (location = 5) in vec2 uv;

// TODO Don't forget this stupid thing
// Normal = mat3(transpose(inverse(model))) * normal;  

out VS_OUT 
{
	vec3 fragPosition;
	vec3 fragNormal;
	vec3 fragColor;
	vec2 fragUv;

	mat3 TBN;
} vs_out;

void main()
{
	vs_out.fragPosition = vec3(u_Model * vec4(position, 1.0));
	vs_out.fragNormal = normal;
	vs_out.fragColor = color;
	vs_out.fragUv = uv;

	vec3 T = normalize(vec3(u_Model * vec4(tangent, 0.0)));
	vec3 N = normalize(vec3(u_Model * vec4(normal, 0.0)));
	T = normalize(T - dot(T, N) * N);
	vec3 B = cross(N, T);

	vs_out.TBN = mat3(T, B, N);

	gl_Position = u_Proj * u_View * u_Model * vec4(position, 1.0);
}