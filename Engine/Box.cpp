#include "pch.h"
#include "Box.h"



Box::~Box()
{
}

void Box::Init()
{
	Object::Init();
	::D3DXCreateBox(DEVICE, m_info.width, m_info.height, m_info.depth,
		&m_pMesh, nullptr);
}

void Box::Awake()
{
	Object::Awake();

}

void Box::Start()
{
	Object::Start();
}

void Box::Update()
{
	Object::Update();
}

void Box::End()
{
	Object::End();
}
