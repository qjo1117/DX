#pragma once

#include "Engine.h"
#include "Transform.h"

/* --------------------------------------------------
					Object
	머테리얼이나 컴포넌트같이 확장성은 버릴껍니다.
	dx9 과제,시험용도로 그짓하기에는 시간이....

	간단하게 구성할 생각이기 때문에 
	Commponent패턴은 갖다 던졌습니다.
	상속으로 해결해볼 생각입니다.
-------------------------------------------------- */

// 망할 업데이트및 정렬 순서 맞춰주기위한 짓
// 이럴꺼면 레이어를 맞춰주는게 나을거같기도하고...
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
	D3DCOLORVALUE   diffuse = Utils::Black();
	D3DCOLORVALUE   ambient = Utils::Black();
	D3DCOLORVALUE   specular = Utils::Black();
	D3DCOLORVALUE   emissive = Utils::Black();
	float           power = 0.0f;   
};

class Object : public enable_shared_from_this<Object>
{
public:
	Object();
	virtual ~Object();

public:
	/* ------- Update Function ------- */
	void Init();
	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void Render();		// 생각해보니 이놈을 굳이? 오버라이딩?
	virtual void End();
	virtual void FinalUpdate();

public:
	/* ------- Helper Function ------- */
	Ref<Transform> GetTransform() { return m_pTransform; }

	void SetName(const wstring& p_strsName);
	const wstring& GetName() { return m_strName; }

	uint32 GetType() { return static_cast<uint32>(m_eType); }
	Material& GetMaterial() { return m_material; }
protected:
	LPD3DXMESH m_pMesh = nullptr;
	Material m_material = {};

	Ref<Transform> m_pTransform = make_shared<Transform>();
	wstring m_strName;
	OBJECT_TYPE m_eType = OBJECT_TYPE::Object;
private:
	static uint64 Count;
};

