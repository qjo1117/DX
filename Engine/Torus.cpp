#include "pch.h"
#include "Torus.h"

void Torus::Init()
{
	Object::Init();

	::D3DXCreateTorus(DEVICE, m_info.innerRadius, m_info.outerRadius, m_info.sides, m_info.rings,
		&m_pMesh, nullptr);
}

void Torus::Awake()
{
	Object::Awake();


}

void Torus::Update()
{
	Object::Update();

}

void Torus::End()
{
	Object::End();
}
