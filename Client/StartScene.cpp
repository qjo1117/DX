#include "pch.h"
#include "StartScene.h"
#include "Engine.h"

#include "Light.h"
#include "Sphere.h"
#include "Box.h"
#include "Camera.h"
#include "Planat.h"

StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

void StartScene::Awake()
{
	INPUT->AddKey("Space", VK_SPACE);
	INPUT->AddKey("Z", 'Z');
	INPUT->AddKey("C", 'C');

	{
		CreatePlanat(L"Sun", Vec3{ 0.0f,0.0f,0.0f }, Utils::One() * 5.0f, 20.0f, Utils::Red());
		CreatePlanat(L"Earth", Vec3{ 5.0f,0.0f,0.0f }, Utils::One() * 0.5f, 10.0f, Utils::Blue(), L"Sun");
		CreatePlanat(L"Mars", Vec3{ 10.0f,0.0f,7.0f }, Utils::One(), 1.0f, Utils::Yellow(), L"Sun");
		CreatePlanat(L"Moon", Vec3{ 2.0f,0.0f,0.0f }, Utils::One() * 0.3f, 10.0f, Utils::White(), L"Earth");
		CreatePlanat(L"Moon_1", Vec3{ 2.0f,0.0f,0.0f }, Utils::One() * 0.3f, 3.0f, Utils::White(), L"Moon");
	}

	{
		m_pPointLight = make_shared<Light>();
		m_pPointLight->Init();
	 	m_pPointLight->SetName(L"Point_Light");
		m_pPointLight->GetLightInfo().type = D3DLIGHTTYPE::D3DLIGHT_POINT;
		m_pPointLight->GetTransform()->SetLocalPosition(Vec3{ 0.0f, 10.0f,0.0f });
		m_pPointLight->GetLightInfo().range = 100.0f;
		m_pPointLight->GetLightInfo().diffuse = Utils::White();
		m_pPointLight->GetLightInfo().attenuation0 = 0.0f;
		m_pPointLight->GetLightInfo().attenuation1 = 0.125f;
		m_pPointLight->GetLightInfo().attenuation2 = 0.0f;
		AddObject(m_pPointLight);
	}

	{
		m_pCamera = make_shared<Camera>();
		m_pCamera->Init();
		m_pCamera->SetName(L"MainCamera");
		m_pCamera->GetTransform()->SetLocalPosition(Vec3{ 0.0f, 50.0f, -100.0f });
		AddObject(m_pCamera);
	}

	// Directional
	{
		Ref<Light> light = make_shared<Light>();
		light->SetName(L"Directional_Light_Down");
		light->GetLightInfo().type = D3DLIGHTTYPE::D3DLIGHT_DIRECTIONAL;
		light->GetLightInfo().direction = Utils::Down();
		AddObject(light);
	}

	// Directional
	{
		Ref<Light> light = make_shared<Light>();
		light->SetName(L"Directional_Light_Up");
		light->GetLightInfo().type = D3DLIGHTTYPE::D3DLIGHT_DIRECTIONAL;
		light->GetLightInfo().direction = Utils::Up();
		AddObject(light);
	}

	Scene::Awake();
}

void StartScene::Update()
{
	Scene::Update();

	if (INPUT->KeyDown("Space")) {
	}
}

void StartScene::End()
{
	Scene::End();
}

void StartScene::CreatePlanat(const wstring& p_strName, const Vec3& pos, const Vec3& scaling, float speed, const Color& color, const wstring& p_strParent)
{
	Ref<Planat> planat = make_shared<Planat>();
	planat->SetName(p_strName);

	planat->GetMaterial().diffuse = color;
	planat->GetMaterial().specular = Utils::White();
	planat->GetMaterial().ambient = color;

	planat->GetTransform()->SetLocalPosition(pos);
	planat->GetTransform()->SetLocalScale(scaling);

	planat->SetSpeed(speed);

	planat->Init();

	if ((p_strParent == L"" || p_strParent.empty()) == false) {
		Ref<Object> parent = FindObject(p_strParent);
		planat->GetTransform()->SetParent(parent->GetTransform());
	}


	AddObject(planat);
}
