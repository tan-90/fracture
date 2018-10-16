#include "Layer.h"

namespace fc
{
	Layer::Layer()
	{

	}

	Layer::Layer(graphics::IRenderer* Renderer)
	{
		m_Renderer = Renderer;

		glm::mat4 Identity;
		m_Renderer->SetProjectionMatrix(Identity);
	}

	Layer::Layer(graphics::IRenderer* Renderer, glm::mat4 Projection)
		:m_Renderer(Renderer)
	{
		m_Renderer->SetProjectionMatrix(Projection);
	}

	Layer::~Layer()
	{
		delete m_Renderer;
	}

	void Layer::PushEntity(Entity* Entity)
	{
		m_Entities.push_back(Entity);
	}

	void Layer::Init()
	{

	}

	void Layer::Update(GLfloat DeltaTime)
	{
	
	}

	void Layer::FixedUpdate()
	{

	}

	void Layer::PreRender()
	{
	}

	void Layer::Render(graphics::Camera* Camera)
	{
		Camera->RenderWorld();

		m_Renderer->SetViewMatrix(Camera->GetViewMatrix());
		m_Renderer->SetCameraPosition(Camera->GetPosition());

		for (Entity* RenderEntity : m_Entities)
		{
			m_Renderer->RenderEntity(RenderEntity);
		}
	}

	void Layer::PostRender()
	{
	}
	void Layer::Finish()
	{
	}
}
