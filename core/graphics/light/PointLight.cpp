#include "PointLight.h"

namespace fc
{
	namespace graphics
	{
		const std::string PointLight::c_PointLightColorLocation = "u_PointLightColors";
		const std::string PointLight::c_PointLightPositionLocation = "u_PointLightPositions";

		PointLight::PointLight(glm::vec3 Position, glm::vec3 Color)
			:ILight(LightType::POINT), m_Position(Position), m_Color(Color)
		{

		}

		void PointLight::Upload(Shader * Shader, int Index)
		{
			Shader->BindUniform(c_PointLightColorLocation + "[" + std::to_string(Index) + "]");
			Shader->BindUniform(c_PointLightPositionLocation + "[" + std::to_string(Index) + "]");

			Shader->UploadUniformFloatVec3(c_PointLightColorLocation + "[" + std::to_string(Index) + "]", m_Color);
			Shader->UploadUniformFloatVec3(c_PointLightPositionLocation + "[" + std::to_string(Index) + "]", m_Position);

		}

		void PointLight::Update()
		{
		}


	}
}
