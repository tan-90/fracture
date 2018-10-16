#pragma once

#include "Component.h"

#include <vector>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\functions.hpp>

#include "..\..\utils\MathUtils.h"

namespace fc
{
	class Transform : public Component
	{
	public:
		Transform();
		Transform(glm::vec3 Position);
		Transform(glm::vec3 Position, glm::vec3 Rotation, glm::vec3 Scale);
		~Transform();

		void Move  (glm::vec3 Offset);
		void Rotate(float Angle, glm::vec3 Axis);
		void Scale (glm::vec3 Scale);

		void SetPosition(glm::vec3 Position);
		void SetRotation(glm::vec3 Rotation);
		void SetScale   (glm::vec3 Scale);

		glm::mat4 GetModelMatrix() const;

	private:
		Transform* m_Parent;
		std::vector<Transform*> m_Children;

		glm::vec3 m_Position;
		glm::vec3 m_Rotation;
		glm::vec3 m_Scale;
	};
}
