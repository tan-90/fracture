#version 330 core

layout (location = 0) in vec3 position;

out vec3 fragUv;

uniform mat4 u_View;
uniform mat4 u_Proj;

void main()
{
	mat4 viewRotation = mat4(mat3(u_View));
	gl_Position = u_Proj * viewRotation * vec4(position, 1.0);
	fragUv = position;
}
