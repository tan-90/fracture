#include "..\applications\Application.h"
#include "..\graphics\camera\FlightCamera.h"

#include "SandboxLayer.h"

#include "..\graphics\renderer\MeshRenderer.h"
#include "..\graphics\Shader.h"

#include "..\graphics\skybox\Skybox.h"
#include "..\graphics\CubeTexture.h"

#include "..\applications\Window.h"

using namespace fc;

class Game : public Application
{
public:
	Game()
		:Application("Sandbox", 1280, 720)
	{
		Init();
	}

	void Init() override
	{
		//Arches_E_PineTree
		//graphics::Texture* EnvironmentMap = new graphics::ImageTexture(utils::FileUtils::ReadHdrImageFile("res/environment/Arches_E_PineTree/Arches_E_PineTree_3k.hdr"), 0, GL_RGB32F, GL_RGB, GL_FLOAT);
		//Ice_Lake
		//graphics::Texture* EnvironmentMap = new graphics::ImageTexture(utils::FileUtils::ReadHdrImageFile("res/environment/Ice_Lake/Ice_Lake_Ref.hdr"), 0, GL_RGB32F, GL_RGB, GL_FLOAT);
		//Milkyway
		//graphics::Texture* EnvironmentMap = new graphics::ImageTexture(utils::FileUtils::ReadHdrImageFile("res/environment/Milkyway/Milkyway_small.hdr"), 0, GL_RGB32F, GL_RGB, GL_FLOAT);
		//Green House
		//graphics::Texture* EnvironmentMap = new graphics::ImageTexture(utils::FileUtils::ReadHdrImageFile("res/environment/Green_House/Greenhouse4_Ref.hdr"), 0, GL_RGB32F, GL_RGB, GL_FLOAT);
		//Cave Room
		//graphics::Texture* EnvironmentMap = new graphics::ImageTexture(utils::FileUtils::ReadHdrImageFile("res/environment/Cave_Room/Cave-Room_Ref.hdr"), 0, GL_RGB32F, GL_RGB, GL_FLOAT);
		//Room
		//graphics::Texture* EnvironmentMap = new graphics::ImageTexture(utils::FileUtils::ReadHdrImageFile("res/environment/Room/Room_Ref.hdr"), 0, GL_RGB32F, GL_RGB, GL_FLOAT);
		//Tropical_Beach
		//graphics::Texture* EnvironmentMap = new graphics::ImageTexture(utils::FileUtils::ReadHdrImageFile("res/environment/Tropical_Beach/Tropical_Beach_3k.hdr"), 0, GL_RGB32F, GL_RGB, GL_FLOAT);
		//Tropical_Ruins
		graphics::Texture* EnvironmentMap = new graphics::ImageTexture(utils::FileUtils::ReadHdrImageFile("res/environment/Tropical_Ruins/TropicalRuins_3k.hdr"), 0, GL_RGB32F, GL_RGB, GL_FLOAT);
		EnvironmentMap->Upload();

		m_Environment = new graphics::EnvironmentMap(EnvironmentMap);
		m_Environment->GenerateSkyboxCubeMap();
		m_Environment->GenerateIrradianceMap();
		m_Environment->GeneratePreFilteredMap();
		m_Environment->GenerateBrdfLookupTexture();

		Pbr = new graphics::Shader("graphics/shaders/vert.glsl", "graphics/shaders/frag.glsl");
		glm::mat4 Projection = glm::perspective(45.0f, 1280 / (float)720, 0.1f, 10000.0f);
		FlightCamera = new graphics::FlightCamera(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		SandboxScene = new Scene(FlightCamera);
		Skybox = new graphics::Skybox(m_Environment->GetCubeTexture(), 1000);
		Skybox->SetProjectionMatrix(Projection);
		Skybox->Upload();
		FlightCamera->SetSkybox(Skybox);
		graphics::MeshRenderer* Renderer = new graphics::MeshRenderer(Pbr);
		Renderer->SetEnvironment(m_Environment);
		
		SandboxLayer* RenderLayer = new SandboxLayer(Renderer, Projection);
		RenderLayer->m_EnvironmentMap = m_Environment;
		SandboxScene->PushLayer(RenderLayer);
		SetScene(SandboxScene);
	}

protected:
	graphics::Shader* Pbr;
	graphics::Camera* FlightCamera;
	graphics::Skybox* Skybox;
	graphics::EnvironmentMap* m_Environment;
	Scene* SandboxScene;
};

int main()
{
	Game g;
	return g.Run();
}