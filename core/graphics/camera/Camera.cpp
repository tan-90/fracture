#include "Camera.h"

#include "..\camera\Camera.h"

namespace fc
{
	namespace graphics
	{
		Camera::Camera(glm::vec3 Position, glm::vec3 Rotation, glm::vec3 Front, glm::vec3 Up)
			:m_Position(Position), m_Rotation(Rotation), m_Front(Front), m_Up(Up)
		{

		}

		Camera::~Camera()
		{

		}

		glm::mat4 Camera::GetViewMatrix()
		{
			return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
		}

		glm::vec3 Camera::GetPosition()
		{
			return m_Position;
		}

		void Camera::RenderWorld()
		{
			if (m_Skybox)
			{
				m_Skybox->Render(this);
			}
		}

		void Camera::Translate(glm::vec3 Offset)
		{
			m_Position += Offset;
		}
		
		void Camera::RotateX(GLfloat Offset)
		{
			m_Rotation.x += Offset;
		}

		void Camera::RotateY(GLfloat Offset)
		{
			m_Rotation.y += Offset;
		}

		void Camera::RotateZ(GLfloat Offset)
		{
			m_Rotation.z += Offset;
		}

		void Camera::SetRotationX(GLfloat Rotation)
		{
			m_Rotation.x = Rotation;
		}
		void Camera::SetRotationY(GLfloat Rotation)
		{
			m_Rotation.y = Rotation;
		}
		void Camera::SetRotationZ(GLfloat Rotation)
		{
			m_Rotation.z = Rotation;
		}
	}
}