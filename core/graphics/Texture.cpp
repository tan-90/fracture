#include "Texture.h"

namespace fc
{
	namespace graphics
	{
		Texture::Texture(GLuint Slot, GLenum Type, GLenum ColorSpace, GLenum InternalColorSpace, GLenum DataType)
			:m_Slot(Slot), m_TextureType(Type), m_ColorSpace(ColorSpace), m_InternalColorSpace(InternalColorSpace), m_DataType(DataType)
		{
			glGenTextures(1, &m_Handle);				
		}

		Texture::~Texture()
		{
			glDeleteTextures(1, &m_Handle);
		}
		void Texture::Bind()
		{
			glActiveTexture(GL_TEXTURE0 + m_Slot);
			glBindTexture(m_TextureType, m_Handle);
		}
		void Texture::Unbind()
		{
			glActiveTexture(GL_TEXTURE0 + m_Slot);
			glBindTexture(m_TextureType, NULL);
		}
		uint Texture::GetByteBufferSize()
		{
			return utils::GLUtils::s_FormatChannelCount[m_InternalColorSpace] * utils::GLUtils::s_TypeSize[m_DataType];
		}
	}
}