#include "pch.h"
#include "Transform.h"
#include "Object.h"

Transform::Transform()
{
}

Transform::~Transform()
{
	
}

void Transform::FinalUpdate()
{
	//if (_change == false) {
	//	return;
	//}
	//_change = false;

	Matrix matScale;
	matScale = Utils::CreateScaling(m_localScale);
	Matrix matRotation = Utils::CreateRotationX(m_localRotation.x);
	matRotation *= Utils::CreateRotationY(m_localRotation.y);
	matRotation *= Utils::CreateRotationZ(m_localRotation.z);
	Matrix matTranslation = Utils::CreateTranslation(m_localPosition);

	m_matLocal = matScale * matRotation * matTranslation;
	m_matWorld = m_matLocal;

	/* ----- �θ� ������� ���������� �̿����ش�. ----- */
	Ref<Transform> parent = GetParent().lock();
	if (parent != nullptr) {
		m_matWorld *= GetParentWorldMatrix(parent);
	}
}

void Transform::SetObj(Ref<class Object> p_pObj)
{
	m_pObj = p_pObj;
}

inline Ref<class Object> Transform::GetObj()
{
	return m_pObj.lock();
}

void Transform::SetParent(Ref<Transform> p_pParent)
{
	if (p_pParent == nullptr) {
		return;
	}
	m_pParent = p_pParent;
	p_pParent->m_vecChilds.push_back(GetObj()->GetTransform());
}

Matrix Transform::GetParentWorldMatrix(WRef<Transform> p_parent)
{
	// TODO : �Ƹ� ����ϴٰ� �ѹ��� �̻����� ������?

	if (p_parent.lock() == nullptr) {
		return Utils::Identity();
	}

	Matrix mat = p_parent.lock()->GetLocalMatrix();
	return mat * GetParentWorldMatrix(p_parent.lock()->GetParent());
}
