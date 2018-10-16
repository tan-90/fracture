#include "MeshRenderer.h"

namespace fc
{
	namespace graphics
	{
		const std::string MeshRenderer::c_ViewMatrixLocation = "u_View";
		const std::string MeshRenderer::c_CameraPositionLocation = "u_CameraPosition";

		const std::string MeshRenderer::c_ProjMatrixLocation = "u_Proj";
		
		const std::string MeshRenderer::c_ModelMatrixLocation = "u_Model";

		const std::string MeshRenderer::c_PointLightCountLocation = "u_PointLightCount";
		const std::string MeshRenderer::c_DirectionalLightCountLocation = "u_DirectionalLightCount";

		const std::string MeshRenderer::c_IrradianceMapLocation = "u_IrradianceMap";
		const std::string MeshRenderer::c_PreFilteredMapLocation = "u_PreFilteredMap";
		const std::string MeshRenderer::c_BrdfLookupTextureLocation = "u_BrdfLookupTexture";

		MeshRenderer::MeshRenderer()
			:IRenderer()
		{
			
		}

		MeshRenderer::MeshRenderer(Shader* Shader)
			:IRenderer(Shader)
		{
			m_Shader->BindUniform(c_ViewMatrixLocation);
			m_Shader->BindUniform(c_CameraPositionLocation);
			m_Shader->BindUniform(c_ProjMatrixLocation);
			m_Shader->BindUniform(c_ModelMatrixLocation);

			m_Shader->BindUniform(c_IrradianceMapLocation);
			m_Shader->BindUniform(c_PreFilteredMapLocation);
			m_Shader->BindUniform(c_BrdfLookupTextureLocation);

			m_Shader->BindUniform(c_PointLightCountLocation);
			m_Shader->BindUniform(c_DirectionalLightCountLocation);
		}

		MeshRenderer::~MeshRenderer()
		{

		}

		void MeshRenderer::SetViewMatrix(glm::mat4 View)
		{
			m_Shader->Enable();
			m_Shader->UploadUniformFloatMat4(c_ViewMatrixLocation, View);
		}
		void MeshRenderer::SetCameraPosition(glm::vec3 Position)
		{
			m_Shader->Enable();
			m_Shader->UploadUniformFloatVec3(c_CameraPositionLocation, Position);
		}
		void MeshRenderer::SetProjectionMatrix(glm::mat4 Proj)
		{
			m_Shader->Enable();
			m_Shader->UploadUniformFloatMat4(c_ProjMatrixLocation, Proj);
		}
		void MeshRenderer::SetModelMatrix(glm::mat4 Model)
		{
			m_Shader->Enable();
			m_Shader->UploadUniformFloatMat4(c_ModelMatrixLocation, Model);
		}
		void MeshRenderer::UploadLights(std::vector<ILight*> Lights)
		{
			int PointLightIndex = 0;
			int DirectionalLightIndex = 0;

			for (ILight* CurrentLight : Lights)
			{
				switch (CurrentLight->GetType())
				{
				case LightType::POINT:
					CurrentLight->Upload(m_Shader, PointLightIndex++);
					break;
				case LightType::DIRECTIONAL:
					CurrentLight->Upload(m_Shader, DirectionalLightIndex++);
					break;
				}
			}

			m_Shader->UploadUniformInt(c_PointLightCountLocation, PointLightIndex);
			m_Shader->UploadUniformInt(c_DirectionalLightCountLocation, DirectionalLightIndex);
		}

		void MeshRenderer::SetEnvironment(EnvironmentMap* Environment)
		{
			m_Environment = Environment;
			m_Shader->UploadUniformInt(c_IrradianceMapLocation, EnvironmentMap::c_IrradianceMapTextureSlot);
			m_Shader->UploadUniformInt(c_PreFilteredMapLocation, EnvironmentMap::c_PreFilteredMapTextureSlot);
			m_Shader->UploadUniformInt(c_BrdfLookupTextureLocation, EnvironmentMap::c_BrdfLookupTextureSlot);
		}

		void MeshRenderer::RenderEntity(Entity* Entity)
		{
			Mesh* MeshComponent;
			MeshComponent = Entity->GetComponentOfType<Mesh>();

			m_Shader->Enable();
			SetProjectionMatrix(glm::perspective(45.0f, 1280 / (float)720, 0.1f, 1000.0f));

			MeshComponent->GetMaterial()->Bind();		

			m_Environment->GetIrradianceMap()->Bind();
			m_Environment->GetPreFilteredMap()->Bind();
			m_Environment->GetBrdfLookupTexture()->Bind();

			Transform* TransformComponent;
			TransformComponent = Entity->GetComponentOfType<Transform>();
			
			SetModelMatrix(TransformComponent->GetModelMatrix());

			MeshComponent->GetVertexArray()->Bind();
			glDrawElements(GL_TRIANGLES, MeshComponent->GetVertexCount(), GL_UNSIGNED_INT, 0);
			MeshComponent->GetVertexArray()->Unbind();

			m_Environment->GetBrdfLookupTexture()->Unbind();
			m_Environment->GetPreFilteredMap()->Unbind();
			m_Environment->GetIrradianceMap()->Unbind();

			MeshComponent->GetMaterial()->Unbind();
			m_Shader->Disable();
		}

	}
}