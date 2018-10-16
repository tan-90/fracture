#pragma once

#include "IRenderer.h"

#include <glm\glm.hpp>

#include "..\ImageTexture.h"
#include "..\VertexArray.h"
#include "..\VertexBuffer.h"


namespace fc
{
	namespace graphics
	{
		struct Vertex
		{
			glm::vec2 Position;
			glm::vec2 Uv;
		};

		class TextureRenderer
		{
		public:
			TextureRenderer(Shader*);
			~TextureRenderer();
			void RenderTexture(ImageTexture* Texture);

		protected:
			void GenerateBufferData();

			Vertex Vertices[6] =
			{
				{{-1.0f,  1.0f}, {0.0f, 1.0f}},
				{{-1.0f, -1.0f}, {0.0f, 0.0f}},
				{{ 1.0f, -1.0f}, {1.0f, 0.0f}},
				 		  	 
				{{-1.0f,  1.0f}, {0.0f, 1.0f}},
				{{ 1.0f, -1.0f}, {1.0f, 0.0f}},
				{{ 1.0f,  1.0f}, {1.0f, 1.0f}}
			};

		private:
			Shader* m_Shader;

			VertexArray* m_VertexArray;
			VertexBuffer* m_VertexBuffer;
		};
	}
}