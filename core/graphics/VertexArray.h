#pragma once

#include <vector>

#include "..\Types.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>

namespace fc
{
	namespace graphics
	{
		class VertexBuffer;
		class IndexBuffer;

		class VertexArray
		{
		public:
			VertexArray();
			~VertexArray();

			VertexBuffer* CreateManagedBuffer();
			void DeleteManagedBuffer(VertexBuffer* Buffer);

			IndexBuffer* CreateIndexBuffer();
			void DeleteIndexBuffer();

			void Bind();
			void Unbind();

		private:
			GLuint m_Handle;

			std::vector<VertexBuffer*> m_ManagedBuffers;
			IndexBuffer* m_IndexBuffer;			
		};
	}
}
