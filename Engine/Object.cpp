#include "pch.h"
#include "Object.h"

uint64 Object::Count = 0;

Object::Object() 
{
	m_strName = L"Object_" + std::to_wstring(Object::Count++);

}

Object::~Object()
{
	m_pTransform = nullptr;

}

void Object::Awake()
{


}

void Object::Start()
{
}

void Object::Update()
{
}

void Object::Render()
{
	if (m_pMesh != nullptr) {
		DEVICE->SetMaterial((D3DMATERIAL9*)&m_material);
		DEVICE->SetTransform(D3DTS_WORLD, &GetTransform()->GetLocalToWorldMatrix());
		m_pMesh->DrawSubset(0);
	}
}

void Object::End()
{
	if (m_pMesh != nullptr) {
		m_pMesh->Release();
		m_pMesh = nullptr;
	}

	m_pTransform = nullptr;
}

void Object::FinalUpdate()
{
	m_pTransform->FinalUpdate();
}

void Object::SetName(const wstring& p_strName)
{
	m_strName = p_strName;
}

void Object::Init()
{
	m_pTransform->SetObj(shared_from_this());
}
