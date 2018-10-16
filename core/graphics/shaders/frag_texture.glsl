#version 400 core

in vec2 fragUv;
out vec3 color;

uniform sampler2D u_Texture;

void main()
{
	vec3 hdrColor = texture(u_Texture, fragUv).rgb;
	
	// Tone mapping
	color = hdrColor / (hdrColor + vec3(1.0));
	
	// Gamma correction
	color = pow(color, vec3(1.0/2.2));
	
}