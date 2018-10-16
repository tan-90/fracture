#include "VertexArray.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace fc
{
	namespace graphics
	{
		VertexArray::VertexArray()
		{
			glGenVertexArrays(1, &m_Handle);
		}

		VertexArray::~VertexArray()
		{
			glDeleteVertexArrays(1, &m_Handle);
		}

		VertexBuffer* VertexArray::CreateManagedBuffer()
		{
			VertexBuffer* Buffer = new VertexBuffer();
			m_ManagedBuffers.push_back(Buffer);

			return Buffer;
		}

		void VertexArray::DeleteManagedBuffer(VertexBuffer* Buffer)
		{
			m_ManagedBuffers.erase(std::find(m_ManagedBuffers.begin(), m_ManagedBuffers.end(), Buffer));
			delete Buffer;
		}

		IndexBuffer* VertexArray::CreateIndexBuffer()
		{
			IndexBuffer* Buffer = new IndexBuffer();
			m_IndexBuffer = Buffer;

			return Buffer;
		}

		void VertexArray::DeleteIndexBuffer()
		{
			delete m_IndexBuffer;
		}

		void VertexArray::Bind()
		{
			glBindVertexArray(m_Handle);
			if (m_IndexBuffer)
			{
				m_IndexBuffer->Bind();
			}
		}

		void VertexArray::Unbind()
		{
			glBindVertexArray(NULL);
			if (m_IndexBuffer)
			{
				m_IndexBuffer->Unbind();
			}
		}
	}
}