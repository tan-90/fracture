#pragma once

#include "..\entity\component\Mesh.h"
#include "..\utils\files\FileUtils.h"
#include "renderer\Framebuffer.h"
#include "camera\Camera.h"
#include "ImageTexture.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

namespace fc
{
	namespace graphics
	{
		class EnvironmentMap
		{
		public:
			EnvironmentMap(Texture* SkyboxEquirectangularMap);

			void GenerateCubeBuffer();
			void GeneratePlaneBuffer();

			void GenerateSkyboxCubeMap();
			void GenerateIrradianceMap();
			void GeneratePreFilteredMap();
			void GenerateBrdfLookupTexture();

			inline CubeTexture* GetCubeTexture() { return (CubeTexture*)m_SkyboxCubeMap; }
			inline CubeTexture* GetIrradianceMap() { return (CubeTexture*)m_IrradianceMap; }
			inline CubeTexture* GetPreFilteredMap() { return(CubeTexture*)m_PreFilteredMap; }
			inline ImageTexture* GetBrdfLookupTexture() { return(ImageTexture*)m_BrdfLookupTexture; }

			static const int c_CubeTextureSlot;
			static const int c_IrradianceMapTextureSlot;
			static const int c_PreFilteredMapTextureSlot;
			static const int c_BrdfLookupTextureSlot;

		private:
			const float m_CubeVertices[108] =
			{
				-1.0f,  1.0f, -1.0f,
				-1.0f, -1.0f, -1.0f,
				 1.0f, -1.0f, -1.0f,
				 1.0f, -1.0f, -1.0f,
				 1.0f,  1.0f, -1.0f,
				-1.0f,  1.0f, -1.0f,

				-1.0f, -1.0f,  1.0f,
				-1.0f, -1.0f, -1.0f,
				-1.0f,  1.0f, -1.0f,
				-1.0f,  1.0f, -1.0f,
				-1.0f,  1.0f,  1.0f,
				-1.0f, -1.0f,  1.0f,

				1.0f, -1.0f, -1.0f,
				1.0f, -1.0f,  1.0f,
				1.0f,  1.0f,  1.0f,
				1.0f,  1.0f,  1.0f,
				1.0f,  1.0f, -1.0f,
				1.0f, -1.0f, -1.0f,

				-1.0f, -1.0f,  1.0f,
				-1.0f,  1.0f,  1.0f,
				 1.0f,  1.0f,  1.0f,
				 1.0f,  1.0f,  1.0f,
				 1.0f, -1.0f,  1.0f,
				-1.0f, -1.0f,  1.0f,

				-1.0f,  1.0f, -1.0f,
				 1.0f,  1.0f, -1.0f,
				 1.0f,  1.0f,  1.0f,
				 1.0f,  1.0f,  1.0f,
				-1.0f,  1.0f,  1.0f,
				-1.0f,  1.0f, -1.0f,

				-1.0f, -1.0f, -1.0f,
				-1.0f, -1.0f,  1.0f,
				 1.0f, -1.0f, -1.0f,
				 1.0f, -1.0f, -1.0f,
				-1.0f, -1.0f,  1.0f,
				 1.0f, -1.0f,  1.0f
			};

			const float m_PlaneVertices[24] =
			{
				-1.0f, -1.0f, 0.0f, 0.0f,
				-1.0f,  1.0f, 0.0f, 1.0f,
				 1.0f, -1.0f, 1.0f, 0.0f,

				-1.0f,  1.0f, 0.0f, 1.0f,
				 1.0f,  1.0f, 1.0f, 1.0f,
				 1.0f, -1.0f, 1.0f, 0.0f
			};

			glm::mat4 m_CubeMapCaptureViews[6] =
			{
				glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
				glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
				glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
				glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
				glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
				glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
			};

			Texture* m_SkyboxEquirectangularMap;
			Texture* m_SkyboxCubeMap;
			Texture* m_IrradianceMap;
			Texture* m_PreFilteredMap;
			Texture* m_BrdfLookupTexture;

			FrameBuffer* m_CubeMapCaptureBuffer;
			FrameBuffer* m_IrradianceMapCaptureBuffer;
			FrameBuffer* m_PreFilteredMapCaptureBuffer;
			FrameBuffer* m_BrdfLookupCaptureBuffer;

			Shader* m_CubeMapCaptureShader;
			Shader* m_IrradianceMapCaptureShader;
			Shader* m_PreFilteredMapCaptureShader;
			Shader* m_BrdfLookupCaptureShader;

			VertexBuffer* m_CubeVertexBuffer;
			VertexArray*  m_CubeVertexArray;
			
			VertexBuffer* m_PlaneVertexBuffer;
			VertexArray*  m_PlaneVertexArray;
		};
	}
}