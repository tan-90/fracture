#include "Scene.h"

namespace fc
{
	Scene::Scene()
		:m_Camera(nullptr)
	{
	}
	Scene::Scene(graphics::Camera* Camera)
		:m_Camera(Camera)
	{
	}
	Scene::~Scene()
	{
		delete m_Camera;
	}

	void Scene::PushLayer(Layer* Layer)
	{
		m_Layers.push_back(Layer);
		Layer->Init();
	}

	void Scene::Init()
	{
		
	}

	void Scene::Update(GLfloat DeltaTime)
	{
		m_Camera->Update(DeltaTime);
		for (Layer* UpdateLayer : m_Layers)
		{
			UpdateLayer->Update(DeltaTime);
		}
	}

	void Scene::FixedUpdate()
	{
		for (Layer* FixedUpdateLayer : m_Layers)
		{
			FixedUpdateLayer->FixedUpdate();
		}
	}

	void Scene::Render()
	{
		for (Layer* RenderLayer : m_Layers)
		{
			RenderLayer->Render(m_Camera);
		}
	}
	void Scene::Finish()
	{
	}
}