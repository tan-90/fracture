#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "..\skybox\Skybox.h"

namespace fc
{
	namespace graphics
	{
		class Camera
		{
		public:
			Camera(glm::vec3 Position, glm::vec3 Rotation, glm::vec3 Front, glm::vec3 Up);
			virtual ~Camera();

			virtual void Update(GLfloat DeltaTime) = 0;

			glm::mat4 GetViewMatrix();
			glm::vec3 GetPosition();

			virtual void RenderWorld();

			virtual void SetSkybox(Skybox* Skybox) { m_Skybox = Skybox; }

		protected:
			glm::vec3 m_Position;
			glm::vec3 m_Rotation;

			glm::vec3 m_Front;
			glm::vec3 m_Up;

			Skybox* m_Skybox;

			// TODO turn the camera into an entity
			void Translate(glm::vec3 Offset);

			void RotateX(GLfloat Offset);
			void RotateY(GLfloat Offset);
			void RotateZ(GLfloat Offset);

			void SetRotationX(GLfloat Rotation);
			void SetRotationY(GLfloat Rotation);
			void SetRotationZ(GLfloat Rotation);
		};
	}
}