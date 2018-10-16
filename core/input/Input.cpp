#include "input.h"

namespace fc
{
	namespace input
	{
		Input* Input::s_Instance = new Input();

		Input::Input()
			:m_CursorPosition({ 0.0f, 0.0f }), m_CursorOffset({ 0.0f, 0.0f})
		{
			for (int i = 0; i < FC_MAX_KEYS; i++)
			{
				m_Keys[i] = false;
			}
			for (int i = 0; i < FC_MAX_BUTTONS; i++)
			{
				m_Buttons[i] = false;
			}
		}

		Input::~Input()
		{
		}

		void Input::KeyCallback(GLFWwindow * Window, int Key, int Scancode, int Action, int Mods)
		{
			GetInstance()->m_Keys[Key] = Action != GLFW_RELEASE;
		}

		void Input::ButtonCallback(GLFWwindow * Window, int Button, int Action, int Mods)
		{
			GetInstance()->m_Buttons[Button] = Action != GLFW_RELEASE;
		}

		void Input::CursorCallback(GLFWwindow * Window, double XPos, double YPos)
		{
			GetInstance()->m_LastCursorPosition = GetInstance()->m_CursorPosition;
			GetInstance()->m_CursorPosition.x = (float)XPos;
			GetInstance()->m_CursorPosition.y = (float)YPos;
		}

		void Input::UpdateOffsets()
		{
			m_CursorOffset = m_CursorPosition - m_LastCursorPosition;
			m_LastCursorPosition = m_CursorPosition;
		}

		
	}
}