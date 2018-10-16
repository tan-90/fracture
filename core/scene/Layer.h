#pragma once

#include <vector>

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>

#include "..\entity\Entity.h"
#include "..\graphics\camera\Camera.h"

#include "..\graphics\renderer\IRenderer.h"

namespace fc
{
	class Layer
	{
	public:
		Layer();
		Layer(graphics::IRenderer* Renderer);
		Layer(graphics::IRenderer* Renderer, glm::mat4 Projection);
		virtual ~Layer();

		void PushEntity(Entity*);

		virtual void Init();
		virtual void Update(GLfloat DeltaTime);
		virtual void FixedUpdate();
		virtual void PreRender();
		virtual void Render(graphics::Camera*);
		virtual void PostRender();
		virtual void Finish();
		
		inline std::vector<Entity*> GetEntities() { return m_Entities; }
		inline graphics::IRenderer* GetRenderer() { return m_Renderer; }

	private:
		std::vector<Entity*> m_Entities;

		graphics::IRenderer* m_Renderer;
	};
}