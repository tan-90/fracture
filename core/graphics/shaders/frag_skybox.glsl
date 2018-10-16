#version 330 core

in vec3 fragUv;

out vec4 color;

uniform samplerCube u_Sampler;

void main()
{
	color = vec4(texture(u_Sampler, fragUv).bgr, 1.0f);
	//color = vec4(textureLod(u_Sampler, fragUv, 2.5).bgr, 1.0f);
}