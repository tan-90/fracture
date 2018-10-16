#include "IndexBuffer.h"

namespace fc
{
	namespace graphics
	{
		void IndexBuffer::Bind()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GetHandle());
		}

		void IndexBuffer::Unbind()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
		}

		void IndexBuffer::UploadInternal()
		{
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, GetBufferSize(), GetBufferData(), GL_STATIC_DRAW);
		}
	}
}