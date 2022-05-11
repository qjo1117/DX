#pragma once

#include "Engine.h"
#include "Transform.h"

/* --------------------------------------------------
					Object
	���׸����̳� ������Ʈ���� Ȯ�强�� �������ϴ�.
	dx9 ����,����뵵�� �����ϱ⿡�� �ð���....

	�����ϰ� ������ �����̱� ������ 
	Commponent������ ���� �������ϴ�.
	������� �ذ��غ� �����Դϴ�.
-------------------------------------------------- */

// ���� ������Ʈ�� ���� ���� �����ֱ����� ��
// �̷����� ���̾ �����ִ°� �����Ű��⵵�ϰ�...
enum class OBJECT_TYPE : uint32
{
	NONE = 0,
	Light,
	Camera,
	Object,
	End,
};

struct Material
{
	D3DCOLORVALUE   diffuse = Utils::White();
	D3DCOLORVALUE   ambient = Utils::White();
	D3DCOLORVALUE   specular = Utils::Black();
	D3DCOLORVALUE   emissive = Utils::Black();
	float           power = 0.0f;   

	void SetSimpleColor(const Color& color, float power = 1.0f) {
		diffuse = color;
		ambient = color * power;
		specular = Utils::White();
	}
};

class Object : public enable_shared_from_this<Object>
{
public:
	Object();
	virtual ~Object();

public:
	/* ------- Update Function ------- */
	virtual void Init();
	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void Render();		// �����غ��� �̳��� ����? �������̵�?
	virtual void End();
	virtual void FinalUpdate();

public:
	/* ------- Helper Function ------- */
	Ref<Transform> GetTransform() { return m_pTransform; }

	void SetName(const wstring& p_strsName);
	const wstring& GetName() { return m_strName; }

	uint32 GetType() { return static_cast<uint32>(m_eType); }
	Material& GetMaterial() { return m_material; }

	void OnMesh() { m_bMesh = true; }		// ��������
	void OffMesh() { m_bMesh = false; }		// �������
	bool GetIsMesh() { return m_bMesh; }	// �⺻����
	void SetIsMesh(bool p_bMesh) { m_bMesh = p_bMesh; }

	void OnEnable() { m_bEnable = true; }		// ��������
	void OffEnable() { m_bEnable = false; }		// �������
	bool GetIsEnable() { return m_bEnable; }	// �⺻����
	void SetIsEnable(bool p_bEnable) { m_bEnable = p_bEnable; }

protected:
	LPD3DXMESH m_pMesh = nullptr;
	Material m_material = {};
	bool m_bMesh = true;
	bool m_bEnable = true;

	Ref<Transform> m_pTransform = make_shared<Transform>();
	wstring m_strName;
	OBJECT_TYPE m_eType = OBJECT_TYPE::Object;

private:
	GENERATE_CLASS_TYPE_INFO(Object)

private:
	static uint64 Count;
};
