#pragma once


/* ----------------------
		Transform
---------------------- */

class Transform
{
public:
	Transform();
	~Transform();

	void FinalUpdate();		// 시점을 맞춰줄려고 이름 이렇게 지음


public:
	/* ---------- Helper Function ---------- */
	const Matrix& GetLocalToWorldMatrix() { return m_matWorld; }
	const Matrix& GetLocalMatrix() { return m_matLocal; }
	Vec3 GetWorldPosition() { return Utils::Translation(m_matWorld); }

	//Vec3 GetRight() { return m_matWorld.Right(); }
	//Vec3 GetUp() { return m_matWorld.Up(); }
	//Vec3 GetForward() { return m_matWorld.Backward(); }

	void SetLocalPosition(const Vec3& position) { m_localPosition = position; }
	void SetLocalRotation(const Vec3& rotation) { m_localRotation = rotation; }
	void SetLocalScale(const Vec3& scale) { m_localScale = scale; }

	Vec3 GetLocalPosition() { return m_localPosition; }
	Vec3 GetLocalRotation() { return m_localRotation; }
	Vec3 GetLocalScale() { return m_localScale; }


	// 더 길어지게 하고 싶지않음
	void Translation(const Vec3& move) { m_localPosition += move; }

	void SetObj(Ref<class Object> p_pObj);
	inline Ref<class Object> GetObj();


	void SetParent(Ref<Transform> p_pParent);
	WRef<Transform> GetParent() { return m_pParent; }
	vector<WRef<Transform>>& GetChilds() { return m_vecChilds; }

	Matrix GetParentWorldMatrix(WRef<Transform> p_parent);

private:
	/* ----- Transform Variable ----- */
	Vec3 m_localPosition = { 0.0f , 0.0f , 0.0f };
	Vec3 m_localRotation = { 0.0f, 0.0f , 0.0f };
	Vec3 m_localScale = { 1.0f, 1.0f ,1.0f };

	Matrix m_matLocal = {};
	Matrix m_matWorld = {};

	WRef<Transform>	m_pParent;
	vector<WRef<Transform>> m_vecChilds;

	WRef<class Object> m_pObj;
};

