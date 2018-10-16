#version 400 core

const float c_PI = 3.141592653;

in vec3 localPosition;

out vec3 fragColor;

uniform samplerCube environmentCubeMap;

void main()
{
	vec3 Irradiance = vec3(0.0);
	
	vec3 Normal = normalize(localPosition);
	vec3 Up     = vec3(0.0, 1.0, 0.0);
	vec3 Right  = cross(Up, Normal);
	     Up     = cross(Normal, Right);
	
	float SampleDelta = 0.025;
	float SampleCount = 0.0;
	
	for(float Phi = 0.0; Phi < 2.0 * c_PI; Phi += SampleDelta)
	{
		for(float Theta = 0.0; Theta < 0.5 * c_PI; Theta += SampleDelta)
		{
			vec3 TangentSample = vec3(sin(Theta) * cos(Phi),  sin(Theta) * sin(Phi), cos(Theta));
			vec3 WorldSample   = TangentSample.x * Right + TangentSample.y * Up + TangentSample.z * Normal;
	
			Irradiance += texture(environmentCubeMap, WorldSample).rgb * cos(Theta) * sin(Theta);
			SampleCount++;
		}
	}
	
	fragColor = c_PI * Irradiance * (1.0 / SampleCount);
	//fragColor = vec3(1.0, 1.0, 0.0);
}