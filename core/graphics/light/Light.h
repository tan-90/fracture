#pragma once

#include "..\..\Types.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

namespace fc
{
	namespace graphics
	{
		enum LightType : uint
		{
			POINT = 0,
			DIRECTIONAL,
			ENVIRONMENT
		};

		class Shader;

		class ILight
		{
		public:
			ILight(LightType Type);
			virtual ~ILight();

			virtual void Upload(Shader* Shader, int Index) = 0;
			virtual void Update();

			inline LightType GetType() { return m_Type; }

		protected:
			LightType m_Type;
		};
	}
}