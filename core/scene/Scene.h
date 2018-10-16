#pragma once

#include <vector>

#include "Layer.h"
#include "..\graphics\camera\Camera.h"
#include "..\graphics\skybox\Skybox.h"

namespace fc
{
	class Scene
	{
	public:

		Scene();
		Scene(graphics::Camera*);
		virtual ~Scene();

		void PushLayer(Layer*);

		void Init();
		void Update(GLfloat DeltaTime);
		void FixedUpdate();
		void Render();
		void Finish();

		inline std::vector<Layer*> GetLayers() { return m_Layers; }

	private:
		std::vector<Layer*> m_Layers;

		graphics::Camera* m_Camera;
	};
}