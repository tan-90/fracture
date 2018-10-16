#pragma once

#include "Light.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <string>

#include <glm\glm.hpp>

#include "..\Shader.h"

namespace fc
{
	namespace graphics
	{
		class PointLight : public ILight
		{
		public:
			PointLight(glm::vec3 Position, glm::vec3 Color);

			void Upload(Shader* Shader, int Index) override;
			void Update() override;
		private:
			glm::vec3 m_Position;
			glm::vec3 m_Color;

			static const std::string c_PointLightColorLocation;
			static const std::string c_PointLightPositionLocation;
		};
	}
}
