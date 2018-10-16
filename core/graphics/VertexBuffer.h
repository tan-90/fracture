#pragma once

#include <map>

#include "GBuffer.h"

namespace fc
{
	namespace graphics
	{
		struct Attribute
		{
			GLint Size;
			GLenum Type;
			GLsizei Stride;
			const void* Pointer;
		};

		class VertexBuffer : public GBuffer
		{
		public:
			VertexBuffer();
			~VertexBuffer();


			void PushAttribute(Attribute Attrib);
			void OverrideAttributeAtLocation(GLuint Location, Attribute Attrib);
			void Bind() override;
			void Unbind() override;

		protected:
			void UploadInternal() override;
			
		private:
			std::map<GLuint, Attribute> m_BufferAttributes;
			GLuint m_AttributeCount;
		};
	}
}
