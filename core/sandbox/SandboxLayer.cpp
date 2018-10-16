#include "SandboxLayer.h"

#define UNIT_TEST

SandboxLayer::SandboxLayer(graphics::IRenderer* Renderer, glm::mat4 Projection)
	:Layer(Renderer, Projection)
{
	m_FrameBuffer = new graphics::FrameBuffer(1280, 720);
}

void SandboxLayer::Init()
{
	utils::Image* Data = new utils::Image();
	Data->Data = NULL;
	Data->Width = 1280;
	Data->Height = 720;
	m_ColorBuffer = new graphics::ImageTexture(Data, 0, GL_RGBA16F, GL_RGBA);
	m_ColorBuffer->DisableMipMapping();
	m_ColorBuffer->Upload();

	m_FrameBuffer->AttachImageTexture(m_ColorBuffer, GL_COLOR_ATTACHMENT0);
	m_FrameBuffer->AttachRenderBuffer(GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT);

	graphics::ILight* PointLight = new graphics::PointLight({ 40.0f, 50.0f, 0.0f }, { 25.0f, 25.0f, 25.0f });
	graphics::ILight* PointLight2 = new graphics::PointLight({ 40.0f, -50.0f, 20.0f }, { 25.0f, 25.0f, 25.0f });
	graphics::ILight* PointLight3 = new graphics::PointLight({ 40.0f, -50.0f, -20.0f }, { 25.0f, 25.0f, 25.0f });

	graphics::ILight* DirectionalLight = new graphics::DirectionalLight({ 1.0f, 1.0f, 1.0f }, { 0.2f, 0.2f, 0.2f });

	std::vector<graphics::ILight*> Lights;

	//Lights.push_back(PointLight);
	//Lights.push_back(PointLight2);
	//Lights.push_back(PointLight3);
	
	//Lights.push_back(DirectionalLight);
	
	((graphics::MeshRenderer*)GetRenderer())->UploadLights(Lights);

	m_ColorBufferShader = new graphics::Shader("graphics/shaders/vert_texture.glsl", "graphics/shaders/frag_texture.glsl");
	m_ColorBufferRenderer = new graphics::TextureRenderer(m_ColorBufferShader);
	m_ColorBufferShader->BindUniform("u_Texture");
	m_ColorBufferShader->UploadUniformInt("u_Texture", 0);
	
	float CurrentRoughness = 0.0f;
	graphics::MaterialFactory Factory(GetRenderer()->GetShader());

	graphics::PbrMaterial* MaterialPlastic;
	graphics::PbrMaterial* MaterialTitanium;
#if defined(UNIT_TEST)
	//MaterialPlastic = Factory.FromDiffuseNormal("res/material/PlasticScuffed", "PlasticScuffed", "png", 0.0f, 1.5f);;
	//MaterialPlastic = Factory.FromDiffuseNormalOcclusionRoughness("res/material/BrickClay", "BrickClay", "jpg", 0.0f);
	//MaterialPlastic = Factory.FromDiffuseNormal("res/material/TitaniumScuffed", "TitaniumScuffed", "png", 1.0f, 0.05f);;
	//MaterialPlastic = Factory.FromUnrealEngine("res/material/Cratered", "CrateredRock", "png");
	//MaterialPlastic = Factory.FromUnrealEngine("res/material/RustedIron", "RustedIron", "png");
	MaterialPlastic = Factory.FromUnrealEngine("res/material/RockCratered", "CrateredRock", "png");
	//MaterialPlastic = Factory.FromDiffuseNormal("res/material/GoldScuffed", "GoldScuffed", "png", 1.0f, 0.0f);;
	MaterialPlastic->Upload();


	Entity* Plastic = new Entity();
	Plastic->AttachComponent(new Transform({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }));
	Plastic->AttachComponent(new Mesh(MeshPrimitives::MATERIAL_BALL, { 1.0f, 1.0f, 1.0f, 1.0f }, MaterialPlastic));
	Plastic->GetComponentOfType<Mesh>()->Upload();
	PushEntity(Plastic);
#else
	
	for (int i = 0; i < 10; i++)
	{
		CurrentRoughness += 0.1f;

		MaterialPlastic = Factory.FromDiffuseNormal("res/material/PlasticScuffed", "PlasticScuffed", "png", 0.0f, CurrentRoughness);;
		//MaterialPlastic = Factory.FromUnrealEngine("res/material/RustedIron", "RustedIron", "png");

		//MaterialPlastic = Factory.FromUnrealEngine("res/material/RockCratered", "CrateredRock", "png");
		MaterialPlastic->Upload();

		Entity* Plastic = new Entity();
		float Offset = -12.5f + 2.5f * i;
		Plastic->AttachComponent(new Transform({ Offset, 0.0f, -1.25f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }));
		Plastic->AttachComponent(new Mesh(
			i % 2 == 0 ? MeshPrimitives::MATERIAL_BALL : MeshPrimitives::ROUNDED_CUBE,
			{ 1.0f, 1.0f, 1.0f, 1.0f }, MaterialPlastic));
		Plastic->GetComponentOfType<Mesh>()->Upload();
		PushEntity(Plastic);

		MaterialTitanium = Factory.FromDiffuseNormal("res/material/GoldScuffed", "GoldScuffed", "png", 1.0f, CurrentRoughness);;
		MaterialTitanium->Upload();

		Entity* Metal = new Entity();
		Offset = -12.5f + 2.5f * i;
		Metal->AttachComponent(new Transform({ Offset, 0.0f, 1.25f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }));
		Metal->AttachComponent(new Mesh(
			i % 2 == 0 ? MeshPrimitives::MATERIAL_BALL : MeshPrimitives::ROUNDED_CUBE,
			{ 1.0f, 1.0f, 1.0f, 1.0f }, MaterialTitanium));
		Metal->GetComponentOfType<Mesh>()->Upload();
		PushEntity(Metal);
	}
#endif
}

void SandboxLayer::Render(graphics::Camera* Camera)
{
	m_FrameBuffer->Bind();
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Layer::Render(Camera);
	m_FrameBuffer->Unbind();

	glDisable(GL_DEPTH_TEST);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	m_ColorBufferRenderer->RenderTexture(m_ColorBuffer);

	if (input::Input::GetInstance()->IsKeyDown(GLFW_KEY_E))
	{
		if (utils::FileUtils::Screenshot("Capture.jpg", 1280, 720))
		{
			std::cout << "Screenshot captured." << std::endl;
		}
	}
}
