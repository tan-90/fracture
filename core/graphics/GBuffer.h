#pragma once

#include "..\Types.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

namespace fc
{
	namespace graphics
	{
		class GBuffer
		{
		public:
			GBuffer();
			virtual ~GBuffer();

			void Upload();

			inline void SetBufferData(byte* Data, GLsizei Size) { m_BufferData = Data; m_BufferSize = Size; }
			inline byte* GetBufferData() { return m_BufferData; }
			inline GLsizei GetBufferSize() { return m_BufferSize; }

			inline const GLuint& GetHandle() const { return m_Handle; }

			virtual void Bind() = 0;
			virtual void Unbind() = 0;

		protected:
			virtual void UploadInternal() = 0;

		private:
			GLuint m_Handle;

			byte* m_BufferData;
			GLsizei m_BufferSize;
		};
	}
}