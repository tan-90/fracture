#pragma once
#include "..\scene\Layer.h"
#include "..\graphics\ImageTexture.h"
#include "..\entity\Entity.h"
#include "..\entity\component\Mesh.h"
#include "..\entity\component\Transform.h"
#include "..\utils\files\FileUtils.h"
#include "..\graphics\Shader.h"
#include "..\graphics\renderer\TextureRenderer.h"
#include "..\graphics\renderer\Framebuffer.h"
#include "..\graphics\material\MaterialFactory.h"
#include "..\graphics\light\PointLight.h"
#include "..\graphics\renderer\MeshRenderer.h"
#include "..\graphics\EnvironmentMap.h"
#include "..\input\Input.h"

using namespace fc;
class SandboxLayer : public Layer
{
public:
	SandboxLayer(graphics::IRenderer* Renderer, glm::mat4 Projection);

	void Init() override;
	void Render(graphics::Camera*) override;

	graphics::EnvironmentMap* m_EnvironmentMap;

	graphics::ImageTexture* m_ColorBuffer;
	graphics::Shader* m_ColorBufferShader;
	graphics::TextureRenderer* m_ColorBufferRenderer;

	graphics::FrameBuffer* m_FrameBuffer;
};