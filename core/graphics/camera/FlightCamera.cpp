#include "FlightCamera.h"

namespace fc
{
	namespace graphics
	{
		FlightCamera::FlightCamera(glm::vec3 Position, glm::vec3 Rotation, glm::vec3 Front, glm::vec3 Up)
			:Camera(Position, Rotation, Front, Up)
		{

		}

		FlightCamera::~FlightCamera()
		{

		}

		void FlightCamera::Update(GLfloat DeltaTime)
		{
			input::Input* InputInstance = input::Input::GetInstance();

			GLfloat TimeCorretedSpeed = m_MoveSpeed * DeltaTime;

			if (InputInstance->IsKeyDown(m_MoveForwardKey))
			{
				Translate(m_Front * TimeCorretedSpeed);
			}
			else if (InputInstance->IsKeyDown(m_MoveBackKey))
			{
				Translate(-m_Front * TimeCorretedSpeed);
			}

			if (InputInstance->IsKeyDown(m_MoveLeftKey))
			{
				Translate(-glm::normalize(glm::cross(m_Front, m_Up)) * TimeCorretedSpeed);
			}
			else if (InputInstance->IsKeyDown(m_MoveRightKey))
			{
				Translate(glm::normalize(glm::cross(m_Front, m_Up)) * TimeCorretedSpeed);
			}

			if (InputInstance->IsKeyDown(m_MoveUpKey))
			{
				Translate(m_Up * TimeCorretedSpeed);
			}
			else if (InputInstance->IsKeyDown(m_MoveDownKey))
			{
				Translate(-m_Up * TimeCorretedSpeed);
			}

			bool DirtyCamera = false;

			if (InputInstance->GetCursorOffset().x != 0)
			{
				DirtyCamera = true;
				RotateX(InputInstance->GetCursorOffset().x * m_LookSensitivity);
			}

			if (InputInstance->GetCursorOffset().y != 0)
			{
				DirtyCamera = true;
				GLfloat NewRotation = m_Rotation.y;
				NewRotation -= InputInstance->GetCursorOffset().y * m_LookSensitivity;
				if (NewRotation > 89.0f)
				{
					SetRotationY(89.0f);
				}
				else if (NewRotation < -89.0f)
				{
					SetRotationY(-89.0f);
				}
				else
				{
					RotateY(-InputInstance->GetCursorOffset().y * m_LookSensitivity);
				}

			}

			if (DirtyCamera)
			{
				glm::vec3 Front;
				Front.x = cos(glm::radians(m_Rotation.x)) * cos(glm::radians(m_Rotation.y));
				Front.y = sin(glm::radians(m_Rotation.y));
				Front.z = sin(glm::radians(m_Rotation.x)) * cos(glm::radians(m_Rotation.y));
				m_Front = glm::normalize(Front);
			}
		}
	}
}