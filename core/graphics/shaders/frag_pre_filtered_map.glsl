#version 330 core

const float c_PI = 3.14159265359;

in vec3 localPosition;

out vec4 fragColor;

uniform samplerCube environmentCubeMap;
uniform float u_Roughness;

vec3 ImportanceSampleGGX(vec2 Xi, vec3 Normal, float Roughness);
float RadicalInverseVanDerCorpus(uint bits);
vec2 Hammersley(uint i, uint N);

float NormalDistributionTrowbridgeRietzGGX(vec3 Normal, vec3 Halfway, float Alpha);

void main()
{
	vec3 Normal = normalize(localPosition);
	vec3 Reflection = Normal;
	vec3 View = Reflection;
	
	const uint c_SampleCount = 512u;
	float TotalWeight = 0.0;
	
	vec3 PreFilteredColor = vec3(0.0);
	for(uint i = 0u; i < c_SampleCount; ++i)
	{
		vec2 Xi = Hammersley(i, c_SampleCount);
		vec3 Halfway = ImportanceSampleGGX(Xi, Normal, u_Roughness);
		vec3 Light = normalize(2.0 * dot(View, Halfway) * Halfway - View);

		float NormalDotLight = max(dot(Normal, Light), 0.0);
		float NormalDotHalfway = max(dot(Normal, Halfway), 0.0);
		float HalfwayDotView = max(dot(Halfway, View), 0.0);

		float Distribution = NormalDistributionTrowbridgeRietzGGX(Normal, Halfway, u_Roughness);
		float ProbabilityDistributionFunction = (Distribution * NormalDotHalfway / (4.0 * HalfwayDotView)) + 0.0001; 
		
		float SampleCubeMapResolution = 1024.0; // resolution of source cubemap (per face)
		float saTexel  = 4.0 * c_PI / (6.0 * SampleCubeMapResolution * SampleCubeMapResolution);
		float saSample = 1.0 / (float(c_SampleCount) * ProbabilityDistributionFunction + 0.0001);
		
		float MipLevel = u_Roughness == 0.0 ? 0.0 : 0.5 * log2(saSample / saTexel); 

		if(NormalDotLight > 0.0)
		{
			PreFilteredColor += textureLod(environmentCubeMap, Light, MipLevel).rgb * NormalDotLight;
			TotalWeight += NormalDotLight;
		}
	}
	
	PreFilteredColor = PreFilteredColor / TotalWeight;
	fragColor = vec4(PreFilteredColor, 1.0);

	//fragColor = texture(environmentCubeMap, localPosition);
}

float RadicalInverseVanDerCorpus(uint bits)
{
	bits = (bits << 16u) | (bits >> 16u);
    bits = ((bits & 0x55555555u) << 1u) | ((bits & 0xAAAAAAAAu) >> 1u);
    bits = ((bits & 0x33333333u) << 2u) | ((bits & 0xCCCCCCCCu) >> 2u);
    bits = ((bits & 0x0F0F0F0Fu) << 4u) | ((bits & 0xF0F0F0F0u) >> 4u);
    bits = ((bits & 0x00FF00FFu) << 8u) | ((bits & 0xFF00FF00u) >> 8u);
    return float(bits) * 2.3283064365386963e-10; // 1.0 / 0x100000000
}

vec2 Hammersley(uint i, uint N)
{
	return vec2(float(i)/float(N), RadicalInverseVanDerCorpus(i));
}

vec3 ImportanceSampleGGX(vec2 Xi, vec3 Normal, float Roughness)
{
    float a = Roughness*Roughness;
	
    float Phi = 2.0 * c_PI * Xi.x;
    float CosTheta = sqrt((1.0 - Xi.y) / (1.0 + (a*a - 1.0) * Xi.y));
    float SinTheta = sqrt(1.0 - CosTheta * CosTheta);
	
    // From spherical coordinates to cartesian coordinates
    vec3 H;
    H.x = cos(Phi) * SinTheta;
    H.y = sin(Phi) * SinTheta;
    H.z = CosTheta;
	
    // From tangent-space vector to world-space sample vector
    vec3 Up = abs(Normal.z) < 0.999 ? vec3(0.0, 0.0, 1.0) : vec3(1.0, 0.0, 0.0);
    vec3 Tangent = normalize(cross(Up, Normal));
    vec3 Bitangent = cross(Normal, Tangent);
	
    vec3 SampleVec = Tangent * H.x + Bitangent * H.y + Normal * H.z;
    return normalize(SampleVec);
}  

float NormalDistributionTrowbridgeRietzGGX(vec3 Normal, vec3 Halfway, float Roughness)
{
	float Alpha = pow(Roughness, 2.0);
	float Alpha2 = Alpha * Alpha;
	float DivisionFactor = c_PI * pow(max(dot(Normal, Halfway), 0.0) * (Alpha2 - 1.0) + 1.0, 2.0);

	return Alpha / DivisionFactor;
}