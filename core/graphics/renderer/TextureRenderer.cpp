#include "TextureRenderer.h"

namespace fc
{
	namespace graphics
	{
		TextureRenderer::TextureRenderer(Shader* Shader)
			:m_Shader(Shader)
		{
			m_VertexArray = new graphics::VertexArray();
			m_VertexArray->Bind();
			m_VertexBuffer = m_VertexArray->CreateManagedBuffer();
			m_VertexArray->Unbind();

			GenerateBufferData();
		}

		TextureRenderer::~TextureRenderer()
		{
			delete m_VertexArray;
			delete m_VertexBuffer;
		}

		void TextureRenderer::RenderTexture(ImageTexture* Texture)
		{
			m_Shader->Enable();
			m_VertexArray->Bind();
			Texture->Bind();
			
			glDrawArrays(GL_TRIANGLES, 0, 6);

			Texture->Unbind();
			m_VertexArray->Unbind();
			m_Shader->Disable();
		}

		void TextureRenderer::GenerateBufferData()
		{
			m_VertexArray->Bind();
			m_VertexBuffer->Bind();

			uint Pointer = 0;
			fc::graphics::Attribute Position;
			Position.Stride = sizeof(Vertex);
			Position.Pointer = (void*)Pointer;
			Position.Type = GL_FLOAT;
			Position.Size = 2;
			Pointer += Position.Size * sizeof(GLfloat);

			fc::graphics::Attribute Uv;
			Uv.Stride = sizeof(Vertex);
			Uv.Pointer = (void*)Pointer;
			Uv.Type = GL_FLOAT;
			Uv.Size = 2;

			m_VertexBuffer->PushAttribute(Position);
			m_VertexBuffer->PushAttribute(Uv);

			m_VertexBuffer->SetBufferData((byte*)Vertices, 6 * sizeof(Vertex));
			m_VertexBuffer->Upload();

			m_VertexBuffer->Unbind();
			m_VertexArray->Unbind();
		}

	}
}

