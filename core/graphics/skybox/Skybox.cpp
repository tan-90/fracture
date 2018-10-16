#include "Skybox.h"

#include "..\camera\Camera.h"

namespace fc
{
	namespace graphics
	{
		const std::string Skybox::c_ViewMatrixLocation = "u_View";
		const std::string Skybox::c_ProjMatrixLocation = "u_Proj";
		const std::string Skybox::c_CubeMapSamplerLocation = "u_Sampler";

		Skybox::Skybox(CubeTexture* Texture)
			:Skybox(Texture, 500)
		{
			
		}

		Skybox::Skybox(CubeTexture* Texture, GLuint Size)
			:m_Size(Size), m_Texture(Texture)
		{
			m_Shader = new graphics::Shader("graphics/shaders/vert_skybox.glsl", "graphics/shaders/frag_skybox.glsl");
			m_Shader->BindUniform(c_ViewMatrixLocation);
			m_Shader->BindUniform(c_ProjMatrixLocation);

			m_Shader->BindUniform(c_CubeMapSamplerLocation);
			m_Shader->UploadUniformInt(c_CubeMapSamplerLocation, GetTexture()->GetSlot());

			m_Vertices = GenerateCubeVertices(m_Size);

			m_VertexArray = new graphics::VertexArray();

			m_VertexArray->Bind();
			m_VertexBuffer = m_VertexArray->CreateManagedBuffer();
			m_VertexArray->Unbind();

		}

		Skybox::~Skybox()
		{
			delete m_Texture;
			delete m_VertexBuffer;
			delete m_Vertices;
		}

		void Skybox::Upload()
		{
			GenerateBuffers();
		}

		void Skybox::SetViewMatrix(glm::mat4 View)
		{
			m_Shader->UploadUniformFloatMat4(c_ViewMatrixLocation, View);
		}

		void Skybox::SetProjectionMatrix(glm::mat4 Proj)
		{
			m_Shader->Enable();
			m_Shader->UploadUniformFloatMat4(c_ProjMatrixLocation, Proj);
		}

		void Skybox::Render(Camera* Camera)
		{
			m_Shader->Enable();

			SetViewMatrix(Camera->GetViewMatrix());

			GetTexture()->Bind();
			GetVertexArray()->Bind();
			glDrawArrays(GL_TRIANGLES, 0, 36);
			GetVertexArray()->Unbind();
			GetTexture()->Unbind();

			m_Shader->Disable();
		}

		GLfloat* Skybox::GenerateCubeVertices(GLfloat Size)
		{
			GLfloat* Vertices = new GLfloat[108]
			{
				-Size,-Size, -Size,
				-Size,-Size, Size,
				-Size, Size, Size,
				Size, Size,-Size,
				-Size,-Size,-Size,
				-Size, Size,-Size,
				Size,-Size, Size,
				-Size,-Size,-Size,
				Size,-Size,-Size,
				Size, Size,-Size,
				Size,-Size,-Size,
				-Size,-Size,-Size,
				-Size,-Size,-Size,
				-Size, Size, Size,
				-Size, Size,-Size,
				Size,-Size, Size,
				-Size,-Size, Size,
				-Size,-Size,-Size,
				-Size, Size, Size,
				-Size,-Size, Size,
				Size,-Size, Size,
				Size, Size, Size,
				Size,-Size,-Size,
				Size, Size,-Size,
				Size,-Size,-Size,
				Size, Size, Size,
				Size,-Size, Size,
				Size, Size, Size,
				Size, Size,-Size,
				-Size, Size,-Size,
				Size, Size, Size,
				-Size, Size,-Size,
				-Size, Size, Size,
				Size, Size, Size,
				-Size, Size, Size,
				Size,-Size, Size
			};
			return Vertices;
		}
		void Skybox::GenerateBuffers()
		{
			m_VertexArray->Bind();
			m_VertexBuffer->Bind();

			m_VertexBuffer->SetBufferData((byte*)m_Vertices, 108 * sizeof(GLfloat));

			Attribute Position;
			Position.Stride = 3 * sizeof(GLfloat);
			Position.Pointer = (void*)0;
			Position.Type = GL_FLOAT;
			Position.Size = 3;
			m_VertexBuffer->PushAttribute(Position);

			m_VertexBuffer->Upload();

			m_VertexBuffer->Unbind();
			m_VertexArray->Unbind();
		}
	}
}