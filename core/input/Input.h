#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>

#include "..\Types.h"

#include <iostream>

#define FC_MAX_KEYS 1024
#define FC_MAX_BUTTONS 256

namespace fc
{
	namespace input
	{
		class Input
		{
		public:
			inline static Input* GetInstance() { return s_Instance; }

			inline const bool& IsKeyDown(int Key) { return m_Keys[Key]; }
			inline const bool& IsButtonDown(int Button) { return m_Buttons[Button]; }
			inline const glm::vec2& GetCursorPosition() { return m_CursorPosition; }
			inline const glm::vec2& GetCursorOffset() { return m_CursorOffset; }

			static void KeyCallback(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods);
			static void ButtonCallback(GLFWwindow* Window, int Button, int Action, int Mods);
			static void CursorCallback(GLFWwindow* Window, double XPos, double YPos);

			void UpdateOffsets();

		private:
			Input();
			~Input();

			static Input* s_Instance;

			bool m_Keys[FC_MAX_KEYS];
			bool m_Buttons[FC_MAX_BUTTONS];

			glm::vec2 m_LastCursorPosition;
			glm::vec2 m_CursorPosition;
			glm::vec2 m_CursorOffset;
		};
	}
}