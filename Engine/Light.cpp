#include "pch.h"
#include "Light.h"

uint32 Light::LightCount = 0;

Light::Light()
{
    m_eType = OBJECT_TYPE::Light;
    m_iIndex = Light::LightCount++;
}

Light::~Light()
{
}

void Light::Awake()
{
    Object::Awake();
}

void Light::FinalUpdate()
{
    Object::FinalUpdate();
    SetLightUpdate();

}

void Light::SetLightUpdate()
{
    m_light.position = GetTransform()->GetWorldPosition();
    
    DEVICE->SetLight(m_iIndex, (D3DLIGHT9*)&m_light);
    DEVICE->LightEnable(m_iIndex, TRUE);
    DEVICE->SetRenderState(D3DRS_LIGHTING, TRUE);
    DEVICE->SetRenderState(D3DRS_AMBIENT, 0x00202020);
}

