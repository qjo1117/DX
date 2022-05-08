#include "pch.h"
#include "Sphere.h"

Sphere::Sphere()
{

}

Sphere::~Sphere()
{
}

void Sphere::Awake()
{
	Object::Awake();
	::D3DXCreateSphere(DEVICE, m_info.radius, m_info.slice, m_info.stack,
		&m_pMesh, nullptr);
}

void Sphere::Start()
{
}

void Sphere::Update()
{

}

void Sphere::End()
{
	Object::End();
}
