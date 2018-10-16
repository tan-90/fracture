#include "IRenderer.h"

namespace fc
{
	namespace graphics
	{
		IRenderer::IRenderer()
			:m_Shader(nullptr)
		{
			//TODO Create default shader factory
		}

		IRenderer::IRenderer(Shader* Shader)
			:m_Shader(Shader)
		{

		}

		IRenderer::~IRenderer()
		{
			SAFE_DELETE(m_Shader);
		}
	}
}