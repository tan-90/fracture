#pragma once

#include "..\..\Types.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "..\ImageTexture.h"

#include <vector>

namespace fc
{
	namespace graphics
	{
		class FrameBuffer
		{
		public:
			FrameBuffer(uint Width, uint Height);
			~FrameBuffer();

			void AttachImageTexture(ImageTexture* Texture, GLenum Usage);
			void AttachRenderBuffer(GLenum Usage, GLenum Attachment);

			void BindRenderBuffer(uint Index);

			void Bind();
			void Unbind();

			inline GLuint GetHandle() { return m_Handle; }

		private:
			GLuint m_Handle;
			uint m_Width;
			uint m_Height;

			std::vector<GLuint> m_RenderBuffers;
		};
	}
}