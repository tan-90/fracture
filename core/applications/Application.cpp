#include "Application.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "Window.h"

namespace fc
{
	Application::Application(std::string Title, uint Width, uint Height)
		:m_Running(false), m_DeltaTime(0), m_ElapsedFixedUpdates(0), m_ElapsedUpdates(0), m_ElapsedFrames(0)
	{
		m_GlobalTimer.Start();
		Init();
		m_Window = new Window(Title, Width, Height);
	}

	Application::~Application()
	{
		Finish();
	}
	
	void Application::Init()
	{
		glfwInit();
	}

	void Application::Finish()
	{
		glfwTerminate();
	}
	
	int Application::Run()
	{
		std::cout << "fractur3 initialization time: " << m_GlobalTimer.Elapsed() << " seconds." << std::endl << std::endl;
		m_Running = true;
		m_UpdateTimer.Start();
		m_RenderTimer.Start();
		m_FixedUpdateTimer.Start();

		while (m_Running)
		{
			m_DeltaTime = m_UpdateTimer.Elapsed();
			m_UpdateTimer.Reset();
			m_ElapsedUpdates++;

			Update();

			if (m_UncappedFrames || m_RenderTimer.Elapsed() >= m_RenderFrequency)
			{
				m_RenderTimer.Reset();
				m_ElapsedFrames++;

				Render();
			}

			if (m_FixedUpdateTimer.Elapsed() >= m_FixedUpdateFrequency)
			{
				m_FixedUpdateTimer.Reset();
				m_ElapsedFixedUpdates++;

				FixedUpdate();
			}

			if (m_ElapsedFixedUpdates >= m_FixedUpdateCount)
			{
				TickSecond();
			}
		}
		return 0;
	}
	
	void Application::Update()
	{
		input::Input::GetInstance()->UpdateOffsets();

		m_CurrentScene->Update(m_DeltaTime);

		m_Window->Update(m_DeltaTime);

		m_Running = !m_Window->ShouldClose();
	}

	void Application::FixedUpdate()
	{
		m_CurrentScene->FixedUpdate();
	}
	
	void Application::Render()
	{
		m_Window->PreRender();
		m_CurrentScene->Render();
		m_Window->PostRender();
	}

	void Application::TickSecond()
	{
		std::cout << "FPS: " << m_ElapsedFrames << std::endl;
		std::cout << "Frame time: " << 1 / (float)m_ElapsedFrames << std::endl;
		if (!m_UncappedFrames)
		{
			std::cout << "UPS: " << m_ElapsedUpdates << std::endl;
			std::cout << "Cycle time: " << 1 / (float)m_ElapsedUpdates << std::endl;
		}
		std::cout << std::endl;

		m_ElapsedFixedUpdates = 0;
		m_ElapsedUpdates = 0;
		m_ElapsedFrames = 0;
	}
	void Application::SetScene(Scene* Scene)
	{
		if (m_CurrentScene)
		{
			m_CurrentScene->Finish();
		}

		m_CurrentScene = Scene;
		m_CurrentScene->Init();
	}
	Scene* Application::GetScene()
	{
		return m_CurrentScene;
	}
}