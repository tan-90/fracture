#version 400 core

const float c_PI = 3.14159265359;

in vec2 fragUv;

out vec2 fragColor;

vec3 ImportanceSampleGGX(vec2 Xi, vec3 Normal, float Roughness);
float RadicalInverseVanDerCorpus(uint bits);
vec2 Hammersley(uint i, uint N);

float GeometrySchlickGGX(vec3 Normal, vec3 Direction, float k);
float GeometrySmith(vec3 Normal, vec3 View, vec3 Light, float k);

vec2 IntegrateBrdf(float NormalDotView, float Roughness);

void main()
{
	vec2 Result = IntegrateBrdf(fragUv.x, fragUv.y);
	fragColor = Result;
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

float GeometrySchlickGGX(vec3 Normal, vec3 Direction, float Roughness)
{
	float k = pow(Roughness, 2.0) / 2.0;

	float NormalDotDirection = max(dot(Normal, Direction), 0.0);
	float DivisionFactor = NormalDotDirection * (1.0 - k) + k;

	return NormalDotDirection / DivisionFactor;
}

float GeometrySmith(vec3 Normal, vec3 View, vec3 Light, float Roughness)
{
	return GeometrySchlickGGX(Normal, View, Roughness) * GeometrySchlickGGX(Normal, Light, Roughness);
}

vec2 IntegrateBrdf(float NormalDotView, float Roughness)
{
	vec3 View;
	View.x = sqrt(1.0 - NormalDotView * NormalDotView);
	View.y = 0.0;
	View.z = NormalDotView;

	float A = 0.0;
	float B = 0.0;

	vec3 Normal = vec3(0.0, 0.0, 1.0);

	const uint c_SampleCount = 512u;
	for(uint i = 0u; i < c_SampleCount; i++)
	{
		vec2 Xi = Hammersley(i, c_SampleCount);
		vec3 Halfway = ImportanceSampleGGX(Xi, Normal, Roughness);
		vec3 Light = normalize(2.0 * dot(View, Halfway) * Halfway - View);

		float NormalDotLight = max(Light.z, 0.0);
		float NormalDotHalfway = max(Halfway.z, 0.0);
		float ViewDotHalfway = max(dot(View, Halfway), 0.0);

		if(NormalDotLight > 0.0)
		{
			float Geometry = GeometrySmith(Normal, View, Light, Roughness);
			float GeometryVis = (Geometry * ViewDotHalfway) / (NormalDotHalfway * NormalDotView);
			float FresnelComponent = pow(1.0 - ViewDotHalfway, 5.0);

			A += (1.0 - FresnelComponent) * GeometryVis;
			B += FresnelComponent * GeometryVis;
		}
	}

	A /= float(c_SampleCount);
	B /= float(c_SampleCount);

	return vec2(A, B);
}