#include "pch.h"
#include "Box.h"



Box::~Box()
{
}

void Box::Awake()
{
	Object::Awake();
	::D3DXCreateBox(DEVICE, m_info.width, m_info.height, m_info.depth,
		&m_pMesh, nullptr);
}

void Box::Start()
{
}

void Box::Update()
{
}

void Box::End()
{
	Object::End();
}
