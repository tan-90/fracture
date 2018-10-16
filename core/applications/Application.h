#pragma once

#include "..\Types.h"
#include "..\utils\Timer.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>
#include <string>

#include "..\scene\Scene.h"

namespace fc
{
	class Window;

	class Application
	{
	public:
		Application(std::string Title, uint Width, uint Height);
		~Application();

		int Run();
		
	protected:
		virtual void Init();
		virtual void Finish();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void TickSecond();

		void SetScene(Scene* Scene);
		Scene* GetScene();

		Window* m_Window;

	private:

		bool m_Running;

		GLfloat m_DeltaTime;

		utils::Timer m_GlobalTimer;
		utils::Timer m_UpdateTimer;
		utils::Timer m_RenderTimer;
		utils::Timer m_FixedUpdateTimer;

		uint m_ElapsedFixedUpdates;
		uint m_ElapsedUpdates;
		uint m_ElapsedFrames;

		const uint m_FixedUpdateCount        = 30;
		const GLfloat m_FixedUpdateFrequency = 1 / (float)m_FixedUpdateCount;
		
		uint m_RenderCount        = 30;
		GLfloat m_RenderFrequency = 1 / (float)m_RenderCount;
		bool m_UncappedFrames     = false;

		Scene* m_CurrentScene;
	};
}
