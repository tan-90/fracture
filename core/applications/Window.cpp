#include "Window.h"

//tmp
#include "..\graphics\VertexBuffer.h"
#include "..\graphics\Shader.h"
#include <glm\glm.hpp>

#include "..\utils\files\AssimpUtils.h"
#include "..\utils\Color.h"
//tmp

namespace fc
{
	Window::Window(std::string Title, uint Width, uint Heigth)
		:m_Title(Title), m_Width(Width), m_Height(Heigth), m_Closed(false)
	{
		m_Handle = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), NULL, NULL);
		RequestContext();
		glewInit();

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

		glfwSetKeyCallback(m_Handle, input::Input::GetInstance()->KeyCallback);
		glfwSetMouseButtonCallback(m_Handle, input::Input::GetInstance()->ButtonCallback);
		glfwSetCursorPosCallback(m_Handle, input::Input::GetInstance()->CursorCallback);

		glfwSetInputMode(m_Handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		glfwSwapInterval(0);
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_Handle);
	}

	void Window::Update(GLfloat DeltaTime)
	{
		glfwPollEvents();

		m_Closed = (glfwWindowShouldClose(m_Handle) == GLFW_TRUE) | input::Input::GetInstance()->IsKeyDown(GLFW_KEY_ESCAPE);
	}

	void Window::FixedUpdate()
	{

	}

	void Window::Clear(utils::Color ClearColor)
	{
		glClearColor(ClearColor.Red, ClearColor.Green, ClearColor.Blue, ClearColor.Alpha);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::PreRender()
	{
		//Clear({ 0.5f, 0.5f, 0.5f, 1.0f });
	}

	void Window::PostRender()
	{
		glfwSwapBuffers(m_Handle);
	}

	void Window::RequestContext() const
	{
		glfwMakeContextCurrent(m_Handle);
	}
}