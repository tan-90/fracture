#pragma once

#include "PbrMaterial.h"
#include "..\..\utils\files\FileUtils.h"
#include "..\Texture.h"
#include "..\Shader.h"

namespace fc
{
	namespace graphics
	{
		class MaterialFactory
		{
		public:
			MaterialFactory(Shader*);
			~MaterialFactory();

			PbrMaterial* FromUnrealEngine(std::string Folder, std::string MaterialName, std::string FileFormat);
			PbrMaterial* FromUnityEngine(std::string Folder, std::string MaterialName , std::string FileFormat);

			PbrMaterial* FromDiffuseNormal(std::string Folder, std::string MaterialName, std::string FileFormat, float Metalness, float Roughness);
			PbrMaterial* FromDiffuseNormalOcclusion(std::string Folder, std::string MaterialName, std::string FileFormat, float Metalness, float Roughness);
			PbrMaterial* FromDiffuseNormalOcclusionRoughness(std::string Folder, std::string MaterialName, std::string FileFormat, float Metalness);
		protected:
			static std::string c_AlbedoSuffix;
			static std::string c_NormalSuffix;
			static std::string c_RoughnessSuffix;
			static std::string c_MetalnessSuffix;
			static std::string c_AmbientOcclusionSuffix;

			Shader* m_Shader;
		};
	}
}