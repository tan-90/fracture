#version 400 core

const float c_PI = 3.141592653;
const vec3  c_F0 = vec3(0.04);

const int c_MaxPointLights = 8;
const int c_MaxDirectionalLights = 8;

uniform int u_PointLightCount;
uniform int u_DirectionalLightCount;

uniform vec3 u_CameraPosition;

uniform sampler2D u_Albedo;
uniform sampler2D u_Normal;
uniform sampler2D u_Roughness;
uniform sampler2D u_Metalness;
uniform sampler2D u_AmbientOcclusion;

uniform samplerCube u_IrradianceMap;
uniform samplerCube u_PreFilteredMap;
uniform sampler2D u_BrdfLookupTexture;

uniform vec3 u_PointLightPositions[c_MaxPointLights];
uniform vec3 u_PointLightColors[c_MaxPointLights];

uniform vec3 u_DirectionalLightDirections[c_MaxDirectionalLights];
uniform vec3 u_DirectionalLightColors[c_MaxDirectionalLights];

in VS_OUT 
{
	vec3 fragPosition;
	vec3 fragNormal;
	vec3 fragColor;
	vec2 fragUv;

	mat3 TBN;
} fs_in;

out vec3 color;

float NormalDistributionTrowbridgeRietzGGX(vec3 Normal, vec3 Halfway, float Alpha);

float GeometrySchlickGGX(vec3 Normal, vec3 Direction, float k);

float GeometrySmith(vec3 Normal, vec3 View, vec3 Light, float k);

vec3  FresnelSchlick(vec3 Normal, vec3 View, vec3 F0, float Roughness);

vec3 PointLightsIrradiance(vec3 FragmentPosition, vec2 FragmentUv, vec3 ViewDirection, vec3 IOR, vec3 FragmentAlbedo, vec3 FragmentNormal, float FragmentRoughness, float FragmentMetalness);
vec3 DirectionalLightsIrradiance(vec3 FragmentPosition, vec2 FragmentUv, vec3 ViewDirection, vec3 IOR, vec3 FragmentAlbedo, vec3 FragmentNormal, float FragmentRoughness, float FragmentMetalness);

void main()
{
	vec3  FragmentAlbedo = texture(u_Albedo, fs_in.fragUv).bgr * fs_in.fragColor.rgb;
	vec3  FragmentNormal = normalize(fs_in.fragNormal + (fs_in.TBN * (texture(u_Normal, fs_in.fragUv).bgr * 2.0 - 1.0)));
	float FragmentRoughness = texture(u_Roughness, fs_in.fragUv).b;
	float FragmentMetalness = texture(u_Metalness, fs_in.fragUv).b;
	vec3  FragmentAmbientOcclusion = texture(u_AmbientOcclusion, fs_in.fragUv).bgr;
	
	vec3 FragmentIrradiance = texture(u_IrradianceMap, FragmentNormal).bgr;
	vec3 FragmentDiffuse = FragmentAlbedo * FragmentIrradiance;
	
	vec3 ViewDirection  = normalize(u_CameraPosition - fs_in.fragPosition);
	
	vec3 IOR = mix(c_F0, FragmentAlbedo, FragmentMetalness);
	
	vec3 LightOut = vec3(0.0);
	
	LightOut += PointLightsIrradiance(fs_in.fragPosition, fs_in.fragUv, ViewDirection, IOR, FragmentAlbedo, FragmentNormal, FragmentRoughness, FragmentMetalness);
	LightOut += DirectionalLightsIrradiance(fs_in.fragPosition, fs_in.fragUv, ViewDirection, IOR, FragmentAlbedo, FragmentNormal, FragmentRoughness, FragmentMetalness);
	
	vec3 kS = FresnelSchlick(FragmentNormal, ViewDirection, IOR, FragmentRoughness);
	vec3 kD = 1.0 - kS;

	vec3 Reflection = reflect(-ViewDirection, FragmentNormal);
	const float c_MaxReflectionDetail = 4.0;
	vec3 PreFilteredColor = textureLod(u_PreFilteredMap, Reflection, FragmentRoughness * c_MaxReflectionDetail).rgb;

	vec2 EnvironmentBrdf = texture(u_BrdfLookupTexture, vec2(max(dot(FragmentNormal, ViewDirection), 0.0), FragmentRoughness)).rg;
	vec3 FragmentSpecular = PreFilteredColor * (kS * EnvironmentBrdf.x + EnvironmentBrdf.y);

	vec3 AmbientLight = (kD * FragmentDiffuse + FragmentSpecular) * FragmentAmbientOcclusion;
	
	color = AmbientLight + LightOut;
	//color = FragmentAlbedo;
	//color = vec3(texture(u_BrdfLookupTexture, vec2(0.0)).rg, 0.0);
	//color = kS;
	//color = fs_in.fragNormal;
	//color = kS;
	//color = vec3(NormalDistributionTrowbridgeRietzGGX(FragmentNormal, ViewDirection, FragmentRoughness));
	//color = (ViewDirection + 1.0) / 2.0;
	//color = texture(u_IrradianceMap, FragmentNormal).bgr;
}

float NormalDistributionTrowbridgeRietzGGX(vec3 Normal, vec3 Halfway, float Roughness)
{
	float Alpha = pow(Roughness, 2.0);
	float Alpha2 = Alpha * Alpha;
	float DivisionFactor = c_PI * pow(max(dot(Normal, Halfway), 0.0) * (Alpha2 - 1.0) + 1.0, 2.0);

	return Alpha / DivisionFactor;
}

float GeometrySchlickGGX(vec3 Normal, vec3 Direction, float Roughness)
{
	float k = pow(Roughness + 1.0, 2.0) / 8.0;

	float NormalDotDirection = max(dot(Normal, Direction), 0.0);
	float DivisionFactor = NormalDotDirection * (1.0 - k) + k;

	return NormalDotDirection / DivisionFactor;
}

float GeometrySmith(vec3 Normal, vec3 View, vec3 Light, float Roughness)
{
	return GeometrySchlickGGX(Normal, View, Roughness) * GeometrySchlickGGX(Normal, Light, Roughness);
}

vec3 FresnelSchlick(vec3 Normal, vec3 View, vec3 F0, float Roughness)
{
	return F0 + (max(vec3(1.0 - Roughness), F0) - F0) * pow(1.0 - max(dot(Normal, View), 0.0), 5.0);
}

vec3 PointLightsIrradiance(vec3 FragmentPosition, vec2 FragmentUv, vec3 ViewDirection, vec3 IOR, vec3 FragmentAlbedo, vec3 FragmentNormal, float FragmentRoughness, float FragmentMetalness)
{
	vec3 LightOut = vec3(0.0);

	// PointLights
	for(int i = 0; i < u_PointLightCount; i++)
	{
		vec3  LightPosition = u_PointLightPositions[i];
		vec3  LightDirection = normalize(LightPosition - FragmentPosition);
		float LightDistance = length(LightPosition - FragmentPosition);
		float LightAttenuation = 1.0 / pow(LightDistance, 2.0);
	
		vec3 HalfwayVector = normalize(LightDirection + ViewDirection); 
	
		vec3 Radiance = u_PointLightColors[i] * LightAttenuation;
	
	
		vec3 Fresnel = FresnelSchlick(HalfwayVector, ViewDirection, IOR, FragmentRoughness);
		float NormalDistribution = NormalDistributionTrowbridgeRietzGGX(FragmentNormal, HalfwayVector, FragmentRoughness);
		float Geometry = GeometrySmith(FragmentNormal, ViewDirection, LightDirection, FragmentRoughness);
	
		vec3 SpecularNominator = NormalDistribution * Geometry * Fresnel;
		float SpecularDenominator = 4 * max(dot(FragmentNormal, ViewDirection), 0.0) * max(dot(FragmentNormal, LightDirection), 0.0);
	
		vec3 Specular = SpecularNominator / (SpecularDenominator + 0.001);
	
		vec3 SpecularComponent = Fresnel;
		vec3 DiffuseComponent = vec3(1.0) - Fresnel;
	
		// Diffuse times 1 minus metalness
		DiffuseComponent *= 1.0 - FragmentMetalness;
	
		float NormalDotLight = max(dot(FragmentNormal, LightDirection), 0.0);
	
		LightOut += (DiffuseComponent * FragmentAlbedo / c_PI + Specular) * Radiance * NormalDotLight;
	}

	return LightOut;
}

vec3 DirectionalLightsIrradiance(vec3 FragmentPosition, vec2 FragmentUv,  vec3 ViewDirection, vec3 IOR, vec3 FragmentAlbedo, vec3 FragmentNormal, float FragmentRoughness, float FragmentMetalness)
{
	vec3 LightOut = vec3(0.0);

	// Directional Lights
	for(int i = 0; i < u_DirectionalLightCount; i++)
	{
		vec3  LightDirection = normalize(u_DirectionalLightDirections[i]);
		vec3 HalfwayVector = normalize(LightDirection + ViewDirection); 
	
		vec3 Radiance = u_DirectionalLightColors[i];
	
	
		vec3 Fresnel = FresnelSchlick(HalfwayVector, ViewDirection, IOR, FragmentRoughness);
		float NormalDistribution = NormalDistributionTrowbridgeRietzGGX(FragmentNormal, HalfwayVector, FragmentRoughness);
		float Geometry = GeometrySmith(FragmentNormal, ViewDirection, LightDirection, FragmentRoughness);
	
		vec3 SpecularNominator = NormalDistribution * Geometry * Fresnel;
		float SpecularDenominator = 4 * max(dot(FragmentNormal, ViewDirection), 0.0) * max(dot(FragmentNormal, LightDirection), 0.0);
	
		vec3 Specular = SpecularNominator / (SpecularDenominator + 0.001);
	
		vec3 SpecularComponent = Fresnel;
		vec3 DiffuseComponent = vec3(1.0) - Fresnel;
	
		// Diffuse times 1 minus metalness
		DiffuseComponent *= 1.0 - texture(u_Metalness, FragmentUv).b;
	
		float NormalDotLight = max(dot(FragmentNormal, LightDirection), 0.0);
	
		LightOut += ((DiffuseComponent * FragmentAlbedo / c_PI) + Specular) * Radiance * NormalDotLight;
	}

	return LightOut;
}