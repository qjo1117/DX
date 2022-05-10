#include "pch.h"
#include "Sphere.h"

Sphere::Sphere()
{

}

Sphere::~Sphere()
{
}

void Sphere::Init()
{
	Object::Init();

	::D3DXCreateSphere(DEVICE, m_info.radius, m_info.slice, m_info.stack,
		&m_pMesh, nullptr);
	
}

void Sphere::Awake()
{
	Object::Awake();

}

void Sphere::Start()
{
	Object::Start();
}

void Sphere::Update()
{
	Object::Update();
}

void Sphere::End()
{
	Object::End();
}
