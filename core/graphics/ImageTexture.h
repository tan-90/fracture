#pragma once

#include "Texture.h"

#include "..\utils\files\FileUtils.h"

namespace fc
{
	namespace graphics
	{
		class ImageTexture : public Texture
		{
		public:
			ImageTexture(utils::Color  Color, GLuint Slot, GLenum ColorSpace = GL_RGBA, GLenum InternalColorSpace = GL_RGBA, GLenum DataType = GL_UNSIGNED_BYTE);
			ImageTexture(utils::Image* Image, GLuint Slot, GLenum ColorSpace = GL_RGBA, GLenum InternalColorSpace = GL_RGBA, GLenum DataType = GL_UNSIGNED_BYTE);
			~ImageTexture();

			void Upload() override;

			inline byte* GetData() { return m_Data; }
			inline uint GetWidth() { return m_Width; }
			inline uint GetHeight() { return m_Height; }
			inline GLenum GetColorSpace() { return m_ColorSpace; }
			inline GLenum GetInternalColorSpace() { return m_InternalColorSpace; }
			
			void GetTexturePixels();

			void DisableMipMapping();

		private:
			uint m_Width;
			uint m_Height;

			bool m_GenMipmaps = true;

			byte* m_Data;
		};
	}
}