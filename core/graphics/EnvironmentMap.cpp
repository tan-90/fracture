#include "EnvironmentMap.h"
#include "..\input\Input.h"

namespace fc
{
	namespace graphics
	{
		const int EnvironmentMap::c_CubeTextureSlot = 10;
		const int EnvironmentMap::c_IrradianceMapTextureSlot = 11;
		const int EnvironmentMap::c_PreFilteredMapTextureSlot = 12;
		const int EnvironmentMap::c_BrdfLookupTextureSlot = 13;

		EnvironmentMap::EnvironmentMap(Texture* SkyboxEquirectangularMap)
			:m_SkyboxEquirectangularMap(SkyboxEquirectangularMap)
		{
			m_CubeMapCaptureShader = new Shader("graphics/shaders/vert_equirectangular_map.glsl", "graphics/shaders/frag_equirectangular_map.glsl");
			m_CubeMapCaptureShader->BindUniform("u_Projection");
			m_CubeMapCaptureShader->UploadUniformFloatMat4("u_Projection", glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f));

			m_CubeMapCaptureShader->BindUniform("u_View");

			m_CubeMapCaptureShader->BindUniform("equirectangularMap");
			m_CubeMapCaptureShader->UploadUniformInt("equirectangularMap", 0);


			m_IrradianceMapCaptureShader = new Shader("graphics/shaders/vert_equirectangular_map.glsl", "graphics/shaders/frag_irradiance_map.glsl");
			m_IrradianceMapCaptureShader->BindUniform("u_Projection");
			m_IrradianceMapCaptureShader->UploadUniformFloatMat4("u_Projection", glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f));

			m_IrradianceMapCaptureShader->BindUniform("u_View");

			m_IrradianceMapCaptureShader->BindUniform("environmentCubeMap");
			m_IrradianceMapCaptureShader->UploadUniformInt("environmentCubeMap", c_CubeTextureSlot);

			m_PreFilteredMapCaptureShader = new Shader("graphics/shaders/vert_equirectangular_map.glsl", "graphics/shaders/frag_pre_filtered_map.glsl");
			m_PreFilteredMapCaptureShader->BindUniform("u_Projection");
			m_PreFilteredMapCaptureShader->UploadUniformFloatMat4("u_Projection", glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f));

			m_PreFilteredMapCaptureShader->BindUniform("u_View");

			m_PreFilteredMapCaptureShader->BindUniform("environmentCubeMap");
			m_PreFilteredMapCaptureShader->UploadUniformInt("environmentCubeMap", c_CubeTextureSlot);

			m_PreFilteredMapCaptureShader->BindUniform("u_Roughness");

			m_BrdfLookupCaptureShader = new Shader("graphics/shaders/vert_brdf_precompute.glsl", "graphics/shaders/frag_brdf_precompute.glsl");


			m_SkyboxCubeMap = new CubeTexture(c_CubeTextureSlot, GL_RGB16F, GL_RGB, GL_FLOAT);
			((CubeTexture*)m_SkyboxCubeMap)->SetWidth(1024);
			((CubeTexture*)m_SkyboxCubeMap)->SetHeight(1024);
			m_SkyboxCubeMap->Upload();

			m_SkyboxCubeMap->Bind();
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			m_SkyboxCubeMap->Unbind();

			m_IrradianceMap = new CubeTexture(c_IrradianceMapTextureSlot, GL_RGB16F, GL_RGB, GL_FLOAT);
			((CubeTexture*)m_IrradianceMap)->SetWidth(32);
			((CubeTexture*)m_IrradianceMap)->SetHeight(32);
			m_IrradianceMap->Upload();

			m_PreFilteredMap = new CubeTexture(c_PreFilteredMapTextureSlot, GL_RGB16F, GL_RGB, GL_FLOAT);
			((CubeTexture*)m_PreFilteredMap)->SetWidth(128);
			((CubeTexture*)m_PreFilteredMap)->SetHeight(128);
			m_PreFilteredMap->Upload();

			m_PreFilteredMap->Bind();
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
			m_PreFilteredMap->Unbind();

			utils::Image* Data = new utils::Image();
			Data->Data = NULL;
			Data->Width = 512;
			Data->Height = 512;
			m_BrdfLookupTexture = new ImageTexture(Data, c_BrdfLookupTextureSlot, GL_RG16F, GL_RG, GL_FLOAT);
			((ImageTexture*)m_BrdfLookupTexture)->DisableMipMapping();
			m_BrdfLookupTexture->Upload();

			m_CubeMapCaptureBuffer = new FrameBuffer(1024, 1024);
			m_CubeMapCaptureBuffer->AttachRenderBuffer(GL_DEPTH_COMPONENT24, GL_DEPTH_ATTACHMENT);

			m_IrradianceMapCaptureBuffer = new FrameBuffer(32, 32);
			m_IrradianceMapCaptureBuffer->AttachRenderBuffer(GL_DEPTH_COMPONENT24, GL_DEPTH_ATTACHMENT);

			m_PreFilteredMapCaptureBuffer = new FrameBuffer(128, 128);
			m_PreFilteredMapCaptureBuffer->AttachRenderBuffer(GL_DEPTH_COMPONENT24, GL_DEPTH_ATTACHMENT);

			m_BrdfLookupCaptureBuffer = new FrameBuffer(512, 512);
			m_BrdfLookupCaptureBuffer->AttachRenderBuffer(GL_DEPTH_COMPONENT24, GL_DEPTH_ATTACHMENT);

			GenerateCubeBuffer();
			GeneratePlaneBuffer();
		}

		void EnvironmentMap::GenerateCubeBuffer()
		{
			m_CubeVertexArray = new VertexArray();
			m_CubeVertexArray->Bind();

			m_CubeVertexBuffer = m_CubeVertexArray->CreateManagedBuffer();
			m_CubeVertexBuffer->Bind();

			m_CubeVertexBuffer->SetBufferData((byte*)m_CubeVertices, 108 * sizeof(float));

			uint Pointer = 0;
			fc::graphics::Attribute Position;
			Position.Stride = 3 * sizeof(float);
			Position.Pointer = (void*)Pointer;
			Position.Type = GL_FLOAT;
			Position.Size = 3;

			m_CubeVertexBuffer->PushAttribute(Position);
			m_CubeVertexBuffer->Upload();

			m_CubeVertexBuffer->Unbind();
			m_CubeVertexArray->Unbind();
		}

		void EnvironmentMap::GeneratePlaneBuffer()
		{
			m_PlaneVertexArray = new VertexArray();
			m_PlaneVertexArray->Bind();

			m_PlaneVertexBuffer = m_PlaneVertexArray->CreateManagedBuffer();
			m_PlaneVertexBuffer->Bind();

			m_PlaneVertexBuffer->SetBufferData((byte*)m_PlaneVertices, 24 * sizeof(float));

			uint Pointer = 0;
			fc::graphics::Attribute Position;
			Position.Stride = 4 * sizeof(GLfloat);
			Position.Pointer = (void*)Pointer;
			Position.Type = GL_FLOAT;
			Position.Size = 2;

			Pointer += Position.Size * sizeof(GLfloat);
			fc::graphics::Attribute Uv;
			Uv.Stride = 4 * sizeof(GLfloat);
			Uv.Pointer = (void*)Pointer;
			Uv.Type = GL_FLOAT;
			Uv.Size = 2;

			m_PlaneVertexBuffer->PushAttribute(Position);
			m_PlaneVertexBuffer->PushAttribute(Uv);

			m_PlaneVertexBuffer->Upload();

			m_PlaneVertexBuffer->Unbind();
			m_PlaneVertexArray->Unbind();
		}

		void EnvironmentMap::GenerateSkyboxCubeMap()
		{
			m_CubeMapCaptureShader->Enable();
			m_SkyboxEquirectangularMap->Bind();

			glViewport(0, 0, 1024, 1024);
			m_CubeMapCaptureBuffer->Bind();
			for (int i = 0; i < 6; i++)
			{
				m_CubeMapCaptureShader->UploadUniformFloatMat4("u_View", m_CubeMapCaptureViews[i]);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, m_SkyboxCubeMap->GetHandle(), 0);
				glDrawBuffer(GL_COLOR_ATTACHMENT0);

				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				m_CubeVertexArray->Bind();
				glDrawArrays(GL_TRIANGLES, 0, 36);
				m_CubeVertexArray->Unbind();
			}

			m_SkyboxCubeMap->Bind();
			glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
			m_SkyboxCubeMap->Unbind();

			m_CubeMapCaptureBuffer->Unbind();
			glViewport(0, 0, 1280, 720);

			m_SkyboxEquirectangularMap->Unbind();
			m_CubeMapCaptureShader->Disable();
		}
		void EnvironmentMap::GenerateIrradianceMap()
		{
			m_IrradianceMapCaptureShader->Enable();
			m_SkyboxCubeMap->Bind();

			glViewport(0, 0, 32, 32);
			m_IrradianceMapCaptureBuffer->Bind();
			for (int i = 0; i < 6; i++)
			{
				m_IrradianceMapCaptureShader->UploadUniformFloatMat4("u_View", m_CubeMapCaptureViews[i]);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, m_IrradianceMap->GetHandle(), 0);
				glDrawBuffer(GL_COLOR_ATTACHMENT0);

				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				m_CubeVertexArray->Bind();
				glDrawArrays(GL_TRIANGLES, 0, 36);
				m_CubeVertexArray->Unbind();
			}
			m_IrradianceMapCaptureBuffer->Unbind();
			glViewport(0, 0, 1280, 720);

			m_SkyboxCubeMap->Unbind();
			m_IrradianceMapCaptureShader->Disable();
		}
		void EnvironmentMap::GeneratePreFilteredMap()
		{
			m_PreFilteredMapCaptureShader->Enable();
			m_SkyboxCubeMap->Bind();

			m_PreFilteredMapCaptureBuffer->Bind();
			uint MipLevels = 5;
			for (uint Mip = 0; Mip < MipLevels; ++Mip)
			{
				uint MipWidth = (uint)(128 * pow(0.5f, Mip));
				uint MipHeight = (uint)(128 * pow(0.5f, Mip));
				m_PreFilteredMapCaptureBuffer->BindRenderBuffer(0);
				glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, MipWidth, MipHeight);
				glViewport(0, 0, MipWidth, MipHeight);

				float Roughness = (float)Mip / (float)(MipLevels - 1);
				m_PreFilteredMapCaptureShader->UploadUniformFloat("u_Roughness", Roughness);

				for (int i = 0; i < 6; i++)
				{
					m_PreFilteredMapCaptureShader->UploadUniformFloatMat4("u_View", m_CubeMapCaptureViews[i]);
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, m_PreFilteredMap->GetHandle(), Mip);
					glDrawBuffer(GL_COLOR_ATTACHMENT0);

					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

					m_CubeVertexArray->Bind();
					glDrawArrays(GL_TRIANGLES, 0, 36);
					m_CubeVertexArray->Unbind();
				}
			}
			m_PreFilteredMapCaptureBuffer->Unbind();
			glViewport(0, 0, 1280, 720);

			m_SkyboxCubeMap->Unbind();
			m_PreFilteredMapCaptureShader->Disable();
		}

		void EnvironmentMap::GenerateBrdfLookupTexture()
		{
			m_BrdfLookupCaptureShader->Enable();

			glViewport(0, 0, 512, 512);
			m_BrdfLookupCaptureBuffer->Bind();

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_BrdfLookupTexture->GetHandle(), 0);
			glDrawBuffer(GL_COLOR_ATTACHMENT0);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			m_PlaneVertexArray->Bind();
			glDrawArrays(GL_TRIANGLES, 0, 6);
			m_PlaneVertexArray->Unbind();

			//((ImageTexture*)m_BrdfLookupTexture)->GetTexturePixels();

			m_BrdfLookupCaptureBuffer->Unbind();
			glViewport(0, 0, 1280, 720);

			m_BrdfLookupCaptureShader->Disable();
		}
	}
}