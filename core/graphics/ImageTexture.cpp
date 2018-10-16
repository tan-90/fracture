#include "ImageTexture.h"

namespace fc
{
	namespace graphics
	{
		ImageTexture::ImageTexture(utils::Color Color, GLuint Slot, GLenum ColorSpace, GLenum InternalColorSpace, GLenum DataType)
			: Texture(Slot, GL_TEXTURE_2D, ColorSpace, InternalColorSpace, DataType)
		{
			m_Width = 1;
			m_Height = 1;			

			m_Data = new byte[4];
			m_Data[0] = (byte)(Color.Red * 255.0f);
			m_Data[1] = (byte)(Color.Green * 255.0f);
			m_Data[2] = (byte)(Color.Blue * 255.0f);
			m_Data[3] = (byte)(Color.Alpha * 255.0f);

			m_ColorSpace = ColorSpace;
			m_InternalColorSpace = InternalColorSpace;
			m_DataType = DataType;

			DisableMipMapping();
		}

		ImageTexture::ImageTexture(utils::Image* Image, GLuint Slot, GLenum ColorSpace, GLenum InternalColorSpace, GLenum DataType)
			:Texture(Slot, GL_TEXTURE_2D, ColorSpace, InternalColorSpace, DataType)
		{
			m_Width = Image->Width;
			m_Height = Image->Height;
			m_Data = Image->Data;
			m_ColorSpace = ColorSpace;
			m_InternalColorSpace = InternalColorSpace;
			m_DataType = DataType;
		}

		ImageTexture::~ImageTexture()
		{
			delete m_Data;
		}

		void ImageTexture::Upload()
		{
			Bind();
			glTexImage2D(GL_TEXTURE_2D, 0, m_ColorSpace, m_Width, m_Height, 0, m_InternalColorSpace, m_DataType, (const void*)m_Data);

			if (m_GenMipmaps)
			{
				glGenerateMipmap(GL_TEXTURE_2D);
			}
			glTexParameteri(GetTextureType(), GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GetTextureType(), GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GetTextureType(), GL_TEXTURE_MIN_FILTER, m_GenMipmaps ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR);
			glTexParameteri(GetTextureType(), GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			Unbind();
		}

		void ImageTexture::GetTexturePixels()
		{
			uint BufferSize = GetByteBufferSize() * m_Width * m_Height;
			m_Data = new byte[BufferSize];

			glGetTextureImage(GetHandle(), 0, GL_RG, GL_FLOAT, BufferSize, m_Data);
		}

		void ImageTexture::DisableMipMapping()
		{
			m_GenMipmaps = false;
		}
	}
}

