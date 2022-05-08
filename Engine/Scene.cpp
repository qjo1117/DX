#include "pch.h"
#include "Scene.h"
#include "Camera.h"

Scene::Scene()
{
	m_vecObjects.reserve(1000);


}

Scene::~Scene()
{
}

void Scene::Awake()
{
	std::sort(m_vecObjects.begin(), m_vecObjects.end(), [](Ref<Object>& a, Ref<Object>& b) { return a->GetType() < b->GetType(); });

	if (m_pCamera == nullptr) {
		for (Ref<Object>& obj : m_vecObjects) {
			if (obj->GetType() == static_cast<uint32>(OBJECT_TYPE::Camera)) {
				m_pCamera = static_pointer_cast<Camera>(obj);
				break;
			}
		}
	} 

	for (Ref<Object>& obj : m_vecObjects) {
		obj->Awake();
	}
}

void Scene::Start()
{
	for (Ref<Object>& obj : m_vecObjects) {
		obj->Start();
	}
}

void Scene::Update()
{
	for (Ref<Object>& obj : m_vecObjects) {
		obj->Update();
	}
}

void Scene::FinalUpdate()
{
	for (Ref<Object>& obj : m_vecObjects) {
		obj->FinalUpdate();
	}

}

void Scene::End()
{
	for (Ref<Object>& obj : m_vecObjects) {
		obj->End();
		obj = nullptr;
	}
	m_vecObjects.clear();

	if (m_pCamera) {
		m_pCamera->End();
		m_pCamera = nullptr;
	}
}

void Scene::Render()
{
	for (Ref<Object>& obj : m_vecObjects) {
		obj->Render();
	}
}

Ref<class Camera> Scene::GetMainCamera()
{
	return m_pCamera;
}

void Scene::AddObject(Ref<Object> p_pObject)
{
	m_vecObjects.push_back(p_pObject);
}

void Scene::RemoveObject(Ref<Object> p_pObject)
{
	auto findGo = std::find(m_vecObjects.begin(), m_vecObjects.end(), p_pObject);
	if (findGo != m_vecObjects.end()) {
		m_vecObjects.erase(findGo);
	}
}

Ref<Object> Scene::FindObject(const wstring& p_strName)
{
	for (Ref<Object>& obj : m_vecObjects) {
		if (obj->GetName().compare(p_strName) == 0) {
			return obj;
		}
	}

	return nullptr;
}
