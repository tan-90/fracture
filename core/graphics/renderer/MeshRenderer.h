#pragma once

#include "IRenderer.h"

#include "..\..\entity\component\Mesh.h"
#include "..\..\entity\component\Transform.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "..\material\PbrMaterial.h"

#include "..\light\Light.h"
#include "..\light\DirectionalLight.h"
#include "Framebuffer.h"

#include "../EnvironmentMap.h"

namespace fc
{
	namespace graphics
	{
		class MeshRenderer : public IRenderer
		{
		public:
			MeshRenderer();
			MeshRenderer(Shader*);
			~MeshRenderer();

			void SetViewMatrix(glm::mat4 View) override;
			void SetCameraPosition(glm::vec3 Position) override;

			void SetProjectionMatrix(glm::mat4 Proj) override;

			void SetModelMatrix(glm::mat4 Model) override;

			void RenderEntity(Entity*) override;

			void UploadLights(std::vector<ILight*> Lights);
			void SetEnvironment(EnvironmentMap* Environment);

			static const std::string c_ViewMatrixLocation;
			static const std::string c_CameraPositionLocation;

			static const std::string c_ProjMatrixLocation;

			static const std::string c_ModelMatrixLocation;

			static const std::string c_PointLightCountLocation;
			static const std::string c_DirectionalLightCountLocation;

			static const std::string c_IrradianceMapLocation;
			static const std::string c_PreFilteredMapLocation;
			static const std::string c_BrdfLookupTextureLocation;

		private:
			EnvironmentMap* m_Environment;
		};
	}
}