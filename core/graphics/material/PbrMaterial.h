#pragma once

#include "..\Shader.h"
#include "..\Texture.h"
#include "..\ImageTexture.h"
#include "..\..\utils\files\FileUtils.h"

#include <string>

namespace fc
{
	namespace graphics
	{
		class PbrMaterial
		{
		public:
			PbrMaterial(Texture* m_Albedo, Texture* m_Normal, Texture* m_Roughness, Texture* Metalness, Texture* m_AmbientOcclusion, Shader* Shader);
			~PbrMaterial();

			void Upload();

			void Bind();
			void Unbind();

			inline void SetAlbedo(Texture* Albedo) { delete m_Albedo; m_Albedo = Albedo; m_Albedo->Upload(); }
			inline void SetNormal(Texture* Normal) { delete m_Normal; m_Normal = Normal; m_Normal->Upload(); }
			inline void SetRoughness(Texture* Roughness) { delete m_Roughness; m_Roughness = Roughness; m_Roughness->Upload(); }
			inline void SetMetalness(Texture* Metalness) { delete m_Metalness; m_Metalness = Metalness; m_Metalness->Upload(); }
			inline void SetAmbientOcclusion(Texture* AmbientOcclusion) { delete m_AmbientOcclusion; m_AmbientOcclusion = AmbientOcclusion; m_AmbientOcclusion->Upload(); }

			static const int c_AlbedoTextureSlot;
			static const int c_NormalTextureSlot;
			static const int c_RoughnessTextureSlot;
			static const int c_MetalnessTextureSlot;
			static const int c_AmbientOcclusionTextureSlot;

		protected:
			static const std::string c_AlbedoTextureSampler;
			static const std::string c_NormalTextureSampler;
			static const std::string c_RoughnessTextureSampler;
			static const std::string c_MetalnessTextureSampler;
			static const std::string c_AmbientOcclusionTextureSampler;

		private:
			Shader* m_Shader;

			Texture* m_Albedo;
			Texture* m_Normal;
			Texture* m_Roughness;
			Texture* m_Metalness;
			Texture* m_AmbientOcclusion;
		};
	}
}
