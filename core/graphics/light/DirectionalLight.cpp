#include "DirectionalLight.h"

namespace fc
{
	namespace graphics
	{
		const std::string DirectionalLight::c_DirectionalLightColorLocation = "u_DirectionalLightColors";
		const std::string DirectionalLight::c_DirectionalLightDirectionLocation = "u_DirectionalLightDirections";

		DirectionalLight::DirectionalLight(glm::vec3 Direction, glm::vec3 Color)
			:ILight(LightType::DIRECTIONAL), m_Direction(Direction), m_Color(Color)
		{

		}

		void DirectionalLight::Upload(Shader* Shader, int Index)
		{
			Shader->BindUniform(c_DirectionalLightColorLocation + "[" + std::to_string(Index) + "]");
			Shader->BindUniform(c_DirectionalLightDirectionLocation + "[" + std::to_string(Index) + "]");
			
			Shader->UploadUniformFloatVec3(c_DirectionalLightColorLocation + "[" + std::to_string(Index) + "]", m_Color);
			Shader->UploadUniformFloatVec3(c_DirectionalLightDirectionLocation + "[" + std::to_string(Index) + "]", m_Direction);
		}

		void DirectionalLight::Update()
		{
		}
	}
}