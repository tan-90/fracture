#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "..\VertexBuffer.h"
#include "..\VertexArray.h"
#include "..\CubeTexture.h"
#include "..\Shader.h"
#include "..\..\entity\component\Component.h"

namespace fc
{
	namespace graphics
	{
		class Camera;
		class Skybox : public Component
		{
		public:
			Skybox(CubeTexture* Texture);
			Skybox(CubeTexture* Texture, GLuint Size);
			~Skybox();

			void Upload();

			void SetViewMatrix(glm::mat4 View);
			void SetProjectionMatrix(glm::mat4 Proj);

			void Render(Camera* Camera);

			inline CubeTexture* GetTexture() { return m_Texture; }
			inline VertexArray* GetVertexArray() { return m_VertexArray; }

		protected:
			static const std::string c_ViewMatrixLocation;
			static const std::string c_ProjMatrixLocation;
			static const std::string c_CubeMapSamplerLocation;

		private:
			GLfloat* GenerateCubeVertices(GLfloat Size);
			void GenerateBuffers();

			GLfloat m_Size;
			GLfloat* m_Vertices;

			CubeTexture* m_Texture;

			VertexArray* m_VertexArray;
			VertexBuffer* m_VertexBuffer;

			Shader* m_Shader;
		};
	}
}