#pragma once

#include "GBuffer.h"

namespace fc
{
	namespace graphics
	{
		class IndexBuffer : public GBuffer
		{
		public:
			void Bind() override;
			void Unbind() override;

		protected:
			void UploadInternal() override;
		};
	}
}