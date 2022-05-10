#pragma once

class Object;

/*----------
	Scene
-----------*/
class Scene : public enable_shared_from_this<Scene>
{
public:
	/* ----- Constructor Function ----- */
	Scene();
	virtual ~Scene();

public:
	/* ----- External Function ----- */
	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void FinalUpdate();
	virtual void End();

	void Render();

	Ref<class Camera> GetMainCamera();

	template<typename T>
	Ref<T> CreateObject();
public:
	/* ----- Helper Function ----- */
	void AddObject(Ref<Object> p_pObject);
	void RemoveObject(Ref<Object> p_pObject);
	Ref<Object> FindObject(const wstring& p_strName);

	const wstring& GetName() { return m_strName; }
	void SetName(const wstring& p_strName) { m_strName = p_strName; }

	vector<Ref<Object>>& GetObjects() { return m_vecObjects; }

protected:
	/* ----- Scene Object Mapping Variable ----- */
	vector<Ref<Object>> m_vecObjects;
	Ref<class Camera> m_pCamera = nullptr;

	wstring m_strName = L"BaseScene";
};

template<typename T>
Ref<T> Scene::CreateObject()
{
	Ref<T> obj = make_shared<T>();
	static_pointer_cast<T>(obj)->Init();
	AddObject(obj);
	return obj;
}