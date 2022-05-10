#include "pch.h"
#include "Spaceship.h"

#include "Sphere.h"
#include "Box.h"
#include "Scene.h"
#include "Camera.h"

Spaceship::~Spaceship()
{
}

void Spaceship::Init()
{
	Object::Init();
	EDITOR->AddEditor([self = static_pointer_cast<Spaceship>(shared_from_this())]() {self->__Editor__Player(); });
}

void Spaceship::Start()
{
	Object::Start();
	m_vecParts.resize(SpacesParts::SPACESPARTS_END);

	GetMaterial().ambient = GetMaterial().diffuse = Utils::White();

	GetTransform()->SetLocalPosition(Utils::Zero());
	GetTransform()->SetLocalRotation(Utils::Zero());
	GetTransform()->SetLocalScale(Utils::One() * 3.0f);

	Ref<Scene> scene = GET_SINGLE(SceneManager)->GetCurrentScene();

	// HEAD
	{
		Ref<Object> obj = m_vecParts[SpacesParts::HEAD];
		obj = scene->CreateObject<Sphere>();
		obj->SetName(m_strName + L"Head");

		obj->GetMaterial().SetSimpleColor(Utils::White());

		Ref<Transform> transform = obj->GetTransform();
		transform->SetLocalMatrix(Utils::One(), Utils::One() * 2.0f, Utils::Forward() * 2.0f);
		transform->SetParent(GetTransform());
	}

	// BODY
	{
		Ref<Object> obj = m_vecParts[SpacesParts::BODY];
		obj = scene->CreateObject<Box>();
		obj->SetName(m_strName + L"Body");

		obj->GetMaterial().SetSimpleColor(Utils::Cyan());

		Ref<Transform> transform = obj->GetTransform();
		transform->SetLocalMatrix(Utils::One() * 2.0f, Utils::One(), Utils::Zero());
		transform->SetParent(GetTransform());
	}

	// RIGHT_HANDLE
	{
		Ref<Object> obj = m_vecParts[SpacesParts::RIGHT_HANDLE];
		obj = scene->CreateObject<Box>();
		obj->SetName(m_strName + L"Right_Handle");

		obj->GetMaterial().SetSimpleColor(Utils::White());

		Ref<Transform> transform = obj->GetTransform();
		transform->SetLocalMatrix(Utils::One(), Vec3{ 1.0f, 0.8f, 0.6f }, Utils::Right() * 1.5f);
		transform->SetParent(GetTransform());
	}

	// LEFT_HANDLE
	{
		Ref<Object> obj = m_vecParts[SpacesParts::LEFT_HANDLE];
		obj = scene->CreateObject<Box>();
		obj->SetName(m_strName + L"Left_Handle");

		obj->GetMaterial().SetSimpleColor(Utils::White());

		Ref<Transform> transform = obj->GetTransform();
		transform->SetLocalMatrix(Vec3{ 1.0f, 0.8f, 0.6f }, Utils::One(), Utils::Left() * 1.5f);
		transform->SetParent(GetTransform());
	}

	// RIGHT_FOOT
	{
		Ref<Object> obj = m_vecParts[SpacesParts::RIGHT_FOOT];
		obj = scene->CreateObject<Box>();
		obj->SetName(m_strName + L"Left_Foot");

		obj->GetMaterial().SetSimpleColor(Utils::White());

		Ref<Transform> transform = obj->GetTransform();
		transform->SetLocalMatrix(Vec3{ 0.5f, 0.3f, 1.0f }, Utils::One(), Utils::BackForward() * 1.5f + Utils::Right() * 0.5f);
		transform->SetParent(GetTransform());
	}

	// LEFT_FOOT
	{
		Ref<Object> obj = m_vecParts[SpacesParts::LEFT_FOOT];
		obj = scene->CreateObject<Box>();
		obj->SetName(m_strName + L"Left_Foot");

		obj->GetMaterial().SetSimpleColor(Utils::White());

		Ref<Transform> transform = obj->GetTransform();
		transform->SetLocalMatrix(Vec3{ 0.5f, 0.3f, 1.0f }, Utils::One(), Utils::BackForward() * 1.5f + Utils::Left() * 0.5f);
		transform->SetParent(GetTransform());
	}

	SetCamera(static_pointer_cast<Camera>(scene->FindObject(L"MainCamera")));

	INPUT->AddKey('1', "OneMode");
	INPUT->AddKey('2', "QuterMode");

	INPUT->AddKey('Q', "Up");
	INPUT->AddKey('E', "Down");
}

void Spaceship::Update()
{
	Object::Update();

	PlayerMove();
	PlayerRotation();

	if (INPUT->KeyDown("OneMode")) {
		m_iMode = PlayerMode::One;
	}
	if (INPUT->KeyDown("QuterMode")) {
		m_iMode = PlayerMode::Quter;
	}


	if (m_iMode == PlayerMode::One) {
		CameraOneMode();
	}
	else {
		CameraQuterMode();
	}

}

void Spaceship::SetCamera(Ref<class Camera> p_pCamera)
{
	m_pCamera = p_pCamera;
}

void Spaceship::PlayerMove()
{
	Vec3 move = Utils::Zero();
	float speed = 100.0f;
	if (INPUT->KeyPress("Right")) {
		move += GetTransform()->GetRight();
	}
	if (INPUT->KeyPress("Left")) {
		move -= GetTransform()->GetRight();
	}
	if (INPUT->KeyPress("Forward")) {
		move += GetTransform()->GetForward();
	}
	if (INPUT->KeyPress("Back")) {
		move -= GetTransform()->GetForward();
	}
	if (INPUT->KeyPress("Up")) {
		move += GetTransform()->GetUp();
	}
	if (INPUT->KeyPress("Down")) {
		move -= GetTransform()->GetUp();
	}

	move *= speed * DELTATIME;

	GetTransform()->Translation(move);
}

void Spaceship::PlayerRotation()
{
	m_defferMouse = m_currentMouse;
	m_currentMouse = INPUT->GetMousePos();

	float speed = 10.0f;
	Vec2 delta = Vec2{ (float)m_currentMouse.x - (float)m_defferMouse.x, (float)m_currentMouse.y - (float)m_defferMouse.y } * speed;

	Vec3 rotation = GetTransform()->GetLocalRotation();
	rotation.y += D3DXToRadian(delta.x * DELTATIME);
	rotation.x += D3DXToRadian(delta.y * DELTATIME);
	GetTransform()->SetLocalRotation(rotation);
}

void Spaceship::CameraOneMode()
{
	if (m_pCamera == nullptr) {
		return;
	}
	Vec3 pos = GetTransform()->GetLocalPosition() + GetTransform()->GetForward() * 3.0f;
	m_pCamera->GetTransform()->SetLocalPosition(pos);
	m_pCamera->GetInfo().look = pos + GetTransform()->GetForward();
}

void Spaceship::CameraQuterMode()
{
	if (m_pCamera == nullptr) {
		return;
	}
	Vec3 pos = Vec3{ 0.0f, 500.0f, -1000.0f };
	m_pCamera->GetTransform()->SetLocalPosition(pos);
	m_pCamera->GetInfo().look = Utils::Zero();
}

void Spaceship::__Editor__Player()
{
	ImGui::Begin(u8"PlayerEditor");

	if (ImGui::Button(u8"One_Mode")) {
		m_iMode = PlayerMode::One;
	}
	ImGui::SameLine();
	if (ImGui::Button(u8"Quter_Mode")) {
		m_iMode = PlayerMode::Quter;
	}


	ImGui::End();
}