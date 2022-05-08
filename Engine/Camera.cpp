#include "pch.h"
#include "Camera.h"

Camera::Camera() 
{
    m_eType = OBJECT_TYPE::Camera;
}

Camera::~Camera()
{
}

void Camera::Awake()
{
    Object::Awake();
}

void Camera::Update()
{
    Object::Update();
    {
        Vec3 move = Utils::Zero();
        float speed = 100.0f;
        if (INPUT->KeyPress("Right")) {
            move.x += speed;
        }
        if (INPUT->KeyPress("Left")) {
            move.x -= speed;
        }
        if (INPUT->KeyPress("Forward")) {
            move.z += speed;
        }
        if (INPUT->KeyPress("Back")) {
            move.z -= speed;
        }

        move *= DELTATIME;

        GetTransform()->Translation(move);
    }
}

void Camera::FinalUpdate()
{
    Object::FinalUpdate();
    

    ViewMatrixUpdate();
    ProjMatrixUpdate();
}

void Camera::ViewMatrixUpdate()
{
    Vec3 eye = GetTransform()->GetWorldPosition();
    D3DXMatrixLookAtLH(&m_matView, &eye, &m_info.look, &m_info.viewUp);
    DEVICE->SetTransform(D3DTS_VIEW, &m_matView);
}

void Camera::ProjMatrixUpdate()
{
    D3DXMatrixPerspectiveFovLH(&m_matProj, m_info.fov, m_info.aspect, m_info.Near, m_info.Far);
    DEVICE->SetTransform(D3DTS_PROJECTION, &m_matProj);
}
