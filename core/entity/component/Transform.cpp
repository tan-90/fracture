#include "Transform.h"

namespace fc
{
	Transform::Transform()
		:m_Position(glm::vec3(0.0f)), m_Rotation(glm::vec3(0.0f)), m_Scale(glm::vec3(1.0f))
	{

	}

	Transform::Transform(glm::vec3 Position)
		:m_Position(Position)
	{

	}

	Transform::Transform(glm::vec3 Position, glm::vec3 Rotation, glm::vec3 Scale)
		:m_Position(Position), m_Rotation(Rotation), m_Scale(Scale)
	{

	}

	void Transform::Move(glm::vec3 Offset)
	{
		m_Position += Offset;
	}

	void Transform::Rotate(float Angle, glm::vec3 Axis)
	{
		m_Rotation += Angle * Axis;
	}

	void Transform::Scale(glm::vec3 Scale)
	{
		m_Scale *= Scale;
	}

	void Transform::SetPosition(glm::vec3 Position)
	{
		m_Position = Position;
	}

	void Transform::SetRotation(glm::vec3 Rotation)
	{
		m_Rotation = Rotation;
	}

	void Transform::SetScale(glm::vec3 Scale)
	{
		m_Scale = Scale;
	}

	Transform::~Transform()
	{

	}

	glm::mat4 Transform::GetModelMatrix() const
	{
		glm::mat4 Model;

		Model = glm::translate(Model, m_Position);

		Model = glm::rotate(Model, utils::MathUtils::ToRadians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		Model = glm::rotate(Model, utils::MathUtils::ToRadians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		Model = glm::rotate(Model, utils::MathUtils::ToRadians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		Model = glm::scale(Model, m_Scale);

		return Model;
	}
}