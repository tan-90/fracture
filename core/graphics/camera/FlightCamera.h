#pragma once

#include "Camera.h"

#include "..\..\input\Input.h"

namespace fc
{
	namespace graphics
	{
		class FlightCamera : public Camera
		{
		public:
			FlightCamera(glm::vec3 Position, glm::vec3 Rotation, glm::vec3 Front, glm::vec3 Up);
			~FlightCamera();
			void Update(GLfloat DeltaTime) override;

		private:
			int m_MoveForwardKey = GLFW_KEY_W;
			int m_MoveBackKey    = GLFW_KEY_S;
			int m_MoveRightKey   = GLFW_KEY_D;
			int m_MoveLeftKey    = GLFW_KEY_A;
			int m_MoveUpKey      = GLFW_KEY_SPACE;
			int m_MoveDownKey    = GLFW_KEY_LEFT_SHIFT;

			GLfloat m_MoveSpeed       = 5.0f;
			GLfloat m_LookSensitivity = 0.05f;
		};
	}
}