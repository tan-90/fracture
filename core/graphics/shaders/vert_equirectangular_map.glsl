#version 400 core

layout (location = 0) in vec3 position;

out vec3 localPosition;

uniform mat4 u_Projection;
uniform mat4 u_View;

void main()
{
	localPosition = position;
	gl_Position = u_Projection * u_View * vec4(localPosition, 1.0);
}