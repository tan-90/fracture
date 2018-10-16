#pragma once

#include "..\Types.h"
#include "..\utils\Color.h"
#include "..\utils\files\FileUtils.h"
#include "..\input\Input.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <string>

#include "..\graphics\camera\FlightCamera.h"
#include "..\entity\component\Mesh.h"
#include "..\entity\Entity.h"
#include "..\graphics\ImageTexture.h"
#include "..\graphics\CubeTexture.h"
#include "..\graphics\skybox\Skybox.h"
#include "..\graphics\renderer\MeshRenderer.h"


namespace fc
{
	class Window
	{
	public:
		Window(std::string Title, uint Width, uint Heigth);
		~Window();

		void Update(GLfloat DeltaTime);
		void FixedUpdate();
		void PreRender();
		void PostRender();

		void Clear(utils::Color ClearColor);

		void RequestContext() const;

		inline const bool& ShouldClose() const { return m_Closed; }
		
	private:
		std::string m_Title;
		uint m_Width;
		uint m_Height;

		bool m_Closed;

		GLFWwindow* m_Handle;

		graphics::FlightCamera* c;
		graphics::Texture* t;
		Entity* Quad;

		Entity* SkyboxEntity;
		graphics::Skybox* m_Skybox;
		graphics::Texture* m_SkyboxTexture;
		graphics::MeshRenderer* m_MeshRenderer;
		fc::graphics::Shader* Program;
	};
}
