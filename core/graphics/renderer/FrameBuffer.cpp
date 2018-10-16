#include "Framebuffer.h"

namespace fc
{
	namespace graphics
	{
		FrameBuffer::FrameBuffer(uint Width, uint Height)
			:m_Width(Width), m_Height(Height)
		{
			glGenFramebuffers(1, &m_Handle);
		}

		FrameBuffer::~FrameBuffer()
		{
			glDeleteFramebuffers(1, &m_Handle);

			for (GLuint Buffer : m_RenderBuffers)
			{
				glDeleteRenderbuffers(1, &Buffer);
			}
		}

		void FrameBuffer::AttachImageTexture(ImageTexture* Texture, GLenum Usage)
		{
			Bind();
			glFramebufferTexture2D(GL_FRAMEBUFFER, Usage, GL_TEXTURE_2D, Texture->GetHandle(), 0);
			glDrawBuffer(GL_COLOR_ATTACHMENT0);
			Unbind();
		}

		void FrameBuffer::AttachRenderBuffer(GLenum Usage, GLenum Attachment)
		{
			Bind();
			GLuint RenderBuffer;
			glGenRenderbuffers(1, &RenderBuffer);
			m_RenderBuffers.push_back(RenderBuffer);

			glBindRenderbuffer(GL_RENDERBUFFER, RenderBuffer);
			glRenderbufferStorage(GL_RENDERBUFFER, Usage, m_Width, m_Height);
			glBindRenderbuffer(GL_RENDERBUFFER, NULL);

			glFramebufferRenderbuffer(GL_FRAMEBUFFER, Attachment, GL_RENDERBUFFER, RenderBuffer);
			Unbind();
		}

		void FrameBuffer::BindRenderBuffer(uint Index)
		{
			glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBuffers.at(Index));
		}

		void FrameBuffer::Bind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_Handle);
		}
		void FrameBuffer::Unbind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, NULL);
		}
	}
}