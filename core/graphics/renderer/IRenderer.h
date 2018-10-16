#pragma once

#include "..\Shader.h"
#include "..\..\Types.h"
#include "..\..\entity\Entity.h"
#include "..\..\utils\MemoryUtils.h"

#include "..\light\Light.h"

#include <glm\glm.hpp>

#include <vector>

namespace fc
{
	namespace graphics
	{		
		class IRenderer
		{
		public:
			IRenderer();
			IRenderer(Shader*);
			virtual ~IRenderer();

			virtual void SetLightSetup(std::vector<ILight> LightSetup) {};

			virtual void SetViewMatrix(glm::mat4 View) = 0;
			virtual void SetCameraPosition(glm::vec3 View) = 0;

			virtual void SetProjectionMatrix(glm::mat4 Proj) = 0;

			virtual void SetModelMatrix(glm::mat4 Model) = 0;

			virtual void RenderEntity(Entity*) = 0;

			inline void SetShader(Shader* Shader) { m_Shader = Shader; }
			inline Shader* GetShader() { return m_Shader; }

		protected:
			Shader* m_Shader;
		};
	}
}