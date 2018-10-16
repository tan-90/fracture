#include "VertexBuffer.h"

namespace fc
{
	namespace graphics
	{
		VertexBuffer::VertexBuffer()
			:GBuffer(), m_AttributeCount(0)
		{

		}

		VertexBuffer::~VertexBuffer()
		{
			GBuffer::~GBuffer();
		}

		void VertexBuffer::UploadInternal()
		{
			glBufferData(GL_ARRAY_BUFFER, GetBufferSize(), GetBufferData(), GL_STATIC_DRAW);

			for (auto Iterator = m_BufferAttributes.begin(); Iterator != m_BufferAttributes.end(); Iterator++)
			{
				GLuint Location = Iterator->first;
				Attribute CurrentAttribute = Iterator->second;

				glVertexAttribPointer(Location, CurrentAttribute.Size, CurrentAttribute.Type, GL_FALSE, CurrentAttribute.Stride, CurrentAttribute.Pointer);
				glEnableVertexAttribArray(Location);
			}
		}

		void VertexBuffer::PushAttribute(Attribute Attrib)
		{
			m_BufferAttributes.insert(std::make_pair(m_AttributeCount, Attrib));
			m_AttributeCount++;
		}

		void VertexBuffer::OverrideAttributeAtLocation(GLuint Location, Attribute Attrib)
		{
			m_BufferAttributes[Location] = Attrib;
		}

		void VertexBuffer::Bind()
		{
			glBindBuffer(GL_ARRAY_BUFFER, GetHandle());
		}

		void VertexBuffer::Unbind()
		{
			glBindBuffer(GL_ARRAY_BUFFER, NULL);
		}
	}
}