#include "PbrMaterial.h"

namespace fc
{
	namespace graphics
	{
		const int PbrMaterial::c_AlbedoTextureSlot          = 0;
		const int PbrMaterial::c_NormalTextureSlot           = 1;
		const int PbrMaterial::c_RoughnessTextureSlot        = 2;
		const int PbrMaterial::c_MetalnessTextureSlot        = 3;
		const int PbrMaterial::c_AmbientOcclusionTextureSlot = 4;

		const std::string PbrMaterial::c_AlbedoTextureSampler          = "u_Albedo";
		const std::string PbrMaterial::c_NormalTextureSampler           = "u_Normal";
		const std::string PbrMaterial::c_RoughnessTextureSampler        = "u_Roughness";
		const std::string PbrMaterial::c_MetalnessTextureSampler        = "u_Metalness";
		const std::string PbrMaterial::c_AmbientOcclusionTextureSampler = "u_AmbientOcclusion";

		PbrMaterial::PbrMaterial(Texture* Albedo, Texture* Normal, Texture* Roughness, Texture* Metalness, Texture* AmbientOcclusion, Shader* Shader)
		{
			m_Shader = Shader;

			m_Albedo = Albedo;
			m_Normal           = Normal;
			m_Roughness        = Roughness;
			m_Metalness        = Metalness;
			m_AmbientOcclusion = AmbientOcclusion;

			m_Shader->Enable();

			m_Shader->BindUniform(c_AlbedoTextureSampler);
			m_Shader->BindUniform(c_NormalTextureSampler);
			m_Shader->BindUniform(c_RoughnessTextureSampler);
			m_Shader->BindUniform(c_MetalnessTextureSampler);
			m_Shader->BindUniform(c_AmbientOcclusionTextureSampler);

			m_Shader->UploadUniformInt(c_AlbedoTextureSampler, c_AlbedoTextureSlot);
			m_Shader->UploadUniformInt(c_NormalTextureSampler, c_NormalTextureSlot);
			m_Shader->UploadUniformInt(c_RoughnessTextureSampler, c_RoughnessTextureSlot);
			m_Shader->UploadUniformInt(c_MetalnessTextureSampler, c_MetalnessTextureSlot);
			m_Shader->UploadUniformInt(c_AmbientOcclusionTextureSampler, c_AmbientOcclusionTextureSlot);

			m_Shader->Disable();
		}
		PbrMaterial::~PbrMaterial()
		{
			delete m_Albedo;
			delete m_Normal;
			delete m_Roughness;
			delete m_Metalness;
			delete m_AmbientOcclusion;
		}
		void PbrMaterial::Upload()
		{
			m_Albedo->Upload();
			m_Normal->Upload();
			m_Roughness->Upload();
			m_Metalness->Upload();
			m_AmbientOcclusion->Upload();
		}
		void PbrMaterial::Bind()
		{
			m_Albedo->Bind();
			m_Normal->Bind();
			m_Roughness->Bind();
			m_Metalness->Bind();
			m_AmbientOcclusion->Bind();
		}
		void PbrMaterial::Unbind()
		{
			m_Albedo->Unbind();
			m_Normal->Unbind();
			m_Roughness->Unbind();
			m_Metalness->Unbind();
			m_AmbientOcclusion->Unbind();
		}
	}
}