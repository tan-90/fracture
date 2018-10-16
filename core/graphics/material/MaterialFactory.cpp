#include "MaterialFactory.h"

namespace fc
{
	namespace graphics
	{
		std::string MaterialFactory::c_AlbedoSuffix = "Albedo";
		std::string MaterialFactory::c_NormalSuffix = "Normal";
		std::string MaterialFactory::c_RoughnessSuffix = "Roughness";
		std::string MaterialFactory::c_MetalnessSuffix = "Metalness";
		std::string MaterialFactory::c_AmbientOcclusionSuffix = "AmbientOcclusion";

		MaterialFactory::MaterialFactory(Shader* Shader)
			:m_Shader(Shader)
		{

		}

		MaterialFactory::~MaterialFactory()
		{

		}

		PbrMaterial* MaterialFactory::FromUnrealEngine(std::string Folder, std::string MaterialName, std::string FileFormat)
		{
			// TODO create texture manage instead of hard coding slots
			Texture* Albedo = new ImageTexture(utils::FileUtils::ReadImageFile(Folder + "/" + MaterialName + "_" + c_AlbedoSuffix + "." + FileFormat), PbrMaterial::c_AlbedoTextureSlot, GL_SRGB_ALPHA, GL_RGBA);
			Texture* Normal = new ImageTexture(utils::FileUtils::ReadImageFile(Folder + "/" + MaterialName + "_" + c_NormalSuffix + "." + FileFormat), PbrMaterial::c_NormalTextureSlot);
			Texture* Roughness  = new ImageTexture(utils::FileUtils::ReadImageFile(Folder + "/" + MaterialName + "_" + c_RoughnessSuffix + "." + FileFormat), PbrMaterial::c_RoughnessTextureSlot);
			Texture* Metalness = new ImageTexture(utils::FileUtils::ReadImageFile(Folder + "/" + MaterialName + "_" + c_MetalnessSuffix + "." + FileFormat), PbrMaterial::c_MetalnessTextureSlot);
			Texture* AmbientOcclusion = new ImageTexture({ 1.0f, 1.0f, 1.0f, 1.0f }, PbrMaterial::c_AmbientOcclusionTextureSlot);
			
			return new PbrMaterial(Albedo, Normal, Roughness, Metalness, AmbientOcclusion, m_Shader);
		}
		PbrMaterial* MaterialFactory::FromUnityEngine(std::string Folder, std::string MaterialName, std::string FileFormat)
		{
			return nullptr;
		}
		PbrMaterial* MaterialFactory::FromDiffuseNormal(std::string Folder, std::string MaterialName, std::string FileFormat, float Metalness, float Roughness)
		{
			Texture* Diffuse = new ImageTexture(utils::FileUtils::ReadImageFile(Folder + "/" + MaterialName + "_" + c_AlbedoSuffix + "." + FileFormat), PbrMaterial::c_AlbedoTextureSlot, GL_SRGB_ALPHA, GL_RGBA);
			Texture* Normal = new ImageTexture(utils::FileUtils::ReadImageFile(Folder + "/" + MaterialName + "_" + c_NormalSuffix + "." + FileFormat), PbrMaterial::c_NormalTextureSlot);
			
			Texture* RoughnessTexture = new ImageTexture({ Roughness, Roughness, Roughness, Roughness }, PbrMaterial::c_RoughnessTextureSlot);
			Texture* MetalnessTexture = new ImageTexture({ Metalness, Metalness, Metalness, Metalness }, PbrMaterial::c_MetalnessTextureSlot);
			Texture* AmbientOcclusion = new ImageTexture({ 1.0f, 1.0f, 1.0f, 1.0f }, PbrMaterial::c_AmbientOcclusionTextureSlot);

			return new PbrMaterial(Diffuse, Normal, RoughnessTexture, MetalnessTexture, AmbientOcclusion, m_Shader);
		}
		PbrMaterial * MaterialFactory::FromDiffuseNormalOcclusion(std::string Folder, std::string MaterialName, std::string FileFormat, float Metalness, float Roughness)
		{
			Texture* Diffuse = new ImageTexture(utils::FileUtils::ReadImageFile(Folder + "/" + MaterialName + "_" + c_AlbedoSuffix + "." + FileFormat), PbrMaterial::c_AlbedoTextureSlot, GL_SRGB_ALPHA, GL_RGBA);
			Texture* Normal = new ImageTexture(utils::FileUtils::ReadImageFile(Folder + "/" + MaterialName + "_" + c_NormalSuffix + "." + FileFormat), PbrMaterial::c_NormalTextureSlot);

			Texture* RoughnessTexture = new ImageTexture({Roughness, Roughness, Roughness, Roughness}, PbrMaterial::c_RoughnessTextureSlot);
			Texture* MetalnessTexture = new ImageTexture({Metalness, Metalness, Metalness, Metalness}, PbrMaterial::c_MetalnessTextureSlot);
			
			Texture* AmbientOcclusion = new ImageTexture(utils::FileUtils::ReadImageFile(Folder + "/" + MaterialName + "_" + c_AmbientOcclusionSuffix + "." + FileFormat), PbrMaterial::c_AmbientOcclusionTextureSlot);

			return new PbrMaterial(Diffuse, Normal, RoughnessTexture, MetalnessTexture, AmbientOcclusion, m_Shader);
		}

		PbrMaterial * MaterialFactory::FromDiffuseNormalOcclusionRoughness(std::string Folder, std::string MaterialName, std::string FileFormat, float Metalness)
		{
			Texture* Diffuse = new ImageTexture(utils::FileUtils::ReadImageFile(Folder + "/" + MaterialName + "_" + c_AlbedoSuffix + "." + FileFormat), PbrMaterial::c_AlbedoTextureSlot, GL_SRGB_ALPHA, GL_RGBA);
			Texture* Normal = new ImageTexture(utils::FileUtils::ReadImageFile(Folder + "/" + MaterialName + "_" + c_NormalSuffix + "." + FileFormat), PbrMaterial::c_NormalTextureSlot);

			Texture* RoughnessTexture = new ImageTexture(utils::FileUtils::ReadImageFile(Folder + "/" + MaterialName + "_" + c_RoughnessSuffix + "." + FileFormat), PbrMaterial::c_RoughnessTextureSlot);
			Texture* MetalnessTexture = new ImageTexture({ Metalness, Metalness, Metalness, Metalness }, PbrMaterial::c_MetalnessTextureSlot);

			Texture* AmbientOcclusion = new ImageTexture(utils::FileUtils::ReadImageFile(Folder + "/" + MaterialName + "_" + c_AmbientOcclusionSuffix + "." + FileFormat), PbrMaterial::c_AmbientOcclusionTextureSlot);

			return new PbrMaterial(Diffuse, Normal, RoughnessTexture, MetalnessTexture, AmbientOcclusion, m_Shader);
		}
	}
}