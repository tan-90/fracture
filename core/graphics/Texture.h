#pragma once

#include "..\Types.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "..\utils\GLUtils.h"
#include "..\utils\files\FileUtils.h"
#include "GBuffer.h"

namespace fc
{
	namespace graphics
	{
		class Texture
		{
		public:
			Texture(GLuint Slot, GLenum Type, GLenum ColorSpace, GLenum InternalColorSpace, GLenum DataType);
			virtual ~Texture();

			void Bind();
			void Unbind();
			virtual void Upload() = 0;

			uint GetByteBufferSize();

			inline GLuint GetHandle() { return m_Handle; }
			inline void SetTextureSlot(GLuint Slot) { m_Slot = Slot; }
			inline GLuint GetSlot() { return m_Slot; }
			inline GLenum GetTextureType() { return m_TextureType; }
			inline void SetHandle(GLuint Handle) { m_Handle = Handle; }

		protected:
			GLenum m_ColorSpace;
			GLenum m_InternalColorSpace;
			GLenum m_DataType;

			GLenum m_TextureType;

		private:
			GLuint m_Handle;
			GLuint m_Slot;

		};
	}
}
