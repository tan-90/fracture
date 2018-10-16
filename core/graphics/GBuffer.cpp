#include "GBuffer.h"

namespace fc
{
	namespace graphics
	{
		GBuffer::GBuffer()
			:m_BufferData(nullptr), m_BufferSize(0)
		{
			glGenBuffers(1, &m_Handle);
		}

		GBuffer::~GBuffer()
		{
			glDeleteBuffers(1, &m_Handle);
		}
		void GBuffer::Upload()
		{
			Bind();
			UploadInternal();
			Unbind();
		}
	}
}