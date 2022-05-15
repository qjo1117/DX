#pragma once

#include "../Engine/EnginePch.h"

#define DEF_EDITOR

#define EDITOR GET_SINGLE(EditorManager)

/* --------- Attribute �䳻���� --------- */
			

#define MENUITEM(Title, Class, Func)					\
inline static struct Register_##Class_##Func			\
{														\
	Register_##Class_##Func()							\
	{													\
		EDITOR->RegisterMenuBar(Title, Class::Func);	\
	}													\
} Register_##Class_##Func					

/* -----------------------------------------------------------------
					Attribute �䳻���� ����
	�Ӽ��� ã�ٰ� property�� ���� ������ �˾ư��� �ڵ��߿� ���÷��Ǹ�
	������ٴ� �ڷḦ ���� �Ǿ����ϴ�.

	���� : Attribute�� ���� �Լ��� �ѹ����̶� ȣ���ϰ� �� �� ������
	MenuItem()�� ���� �۾��� ������ �� ���� ���̴�.
	�׷��� �ڷḦ ã������ �Ӽ����� �Լ�ȣ�� ���ɿ��� ���ַ� ã�ҽ��ϴ�.

	Reflection ������ ���ٰ� ������ ���ε� �𸮾󿡼��� ��ũ�θ�
	���� �̿��߽��ϴ�.
	�� ���� �����غ��� ���� �Ӽ��� ã�� �ʿ���� ��ũ�θ� �Ӽ�ó��
	����ϴ� ���� ���? ��� ������ ��鼭 ��ũ�ο� �ִ�
	static struct A { A() {} } a(); ȣ�� ����� ���� �翴���ϴ�.
	static�ΰ� ������ �ȵ����� ������ '�Լ� ȣ��'�� �����ϴٴ� ������
	�� �� �־����ϴ�.

	�� �ڷδ� �����ϰ� �����߽��ϴ�.
----------------------------------------------------------------- */


#define LOG(log, state) EDITOR->Log(log, state)


enum LOG_STATE : uint8
{
	NONE = 0,
	LOG		= 1 << 1,
	WARNING = 1 << 2,
	ERROR_	= 1 << 3,
	LOG_STATE_END
};

class IEditor
{
public:
	IEditor() {}
	virtual ~IEditor() {}

	virtual void Show() = 0;
	virtual void End() {};
	void ShowEditor() { ImGui::Begin(Title.c_str()); Show(); ImGui::End(); }

	/* ------ Property ------ */
	PRIVATE_PROPERTY(string, Title) = typeid(IEditor).name();
};

class MenuInfo : public enable_shared_from_this<MenuInfo>
{
public:
	bool IsMenuItem() { return vecChildMenu.empty(); }
	bool IsMenuBar() { return !vecChildMenu.empty(); }

public:
	/* ------ Property ------ */
	PRIVATE_PROPERTY(string, strTitle);
	PRIVATE_PROPERTY(vector<Ref<MenuInfo>>, vecChildMenu);
	PRIVATE_PROPERTY(function<void(void)>, FuncOn);
};


class EditorManager
{
	DECLARE_SINGLE(EditorManager);
public:
	
	void Init(HWND hWnd);
	void Update();
	void Render();
	void End();

public:
	void RegisterEditor(function<void(void)> p_editor);
	
	template<typename T>
	T* GetWindow();

public:
	void MainMenuBar();

	void RegisterMenuBar(const string& p_title, function<void(void)> p_func);
	Ref<MenuInfo> Ref_FindMenuBar(Ref<MenuInfo>& p_info, const vector<string>& title, int32 index = 0);
	void Ref_MenuPresent(Ref<MenuInfo>& p_info);
public:
	
	/* ----- Log ------ */
	void ConsoleEditor();
	void Log(const string& log, uint8 state = LOG_STATE::LOG);
	void Clear(uint8 state  = LOG_STATE::LOG | LOG_STATE::ERROR_ | LOG_STATE::WARNING);

	void PushEditor(IEditor* editor);

private:
	/* ----- Editor ------ */
	ImGuiIO* m_pInfo = nullptr;
	HWND m_hWnd = nullptr;

	vector<IEditor*> m_vecEditor;

	/* ----- Log ------ */
	uint8 m_eState = LOG_STATE::LOG | LOG_STATE::WARNING | LOG_STATE::ERROR_;
	array<vector<string>, 3> m_arrLogs;

	/* ------ Menu Tree ------ */
	Ref<MenuInfo> m_pMenuBar = make_shared<MenuInfo>();
};

/* ---------------------------------------------------------------------
	������ ������ѱ� �������
	shared_ptr ������� ������ ���µ��� Object���η� �Լ��� ȣ���ϴ� ��찡 ���.
	������� �ص� ���� �׳� DX9 ���� ��ü������ ����鿡�� �����ֱ⵵ �������̰�
	�������� �͵� Ŭ���� ���̾�׷����� ǥ���� �����ϱ⶧���̴�.
	
	������ Editor�� �ִ� �������� ��¦ �ָ��� ���� �����.
	Unityó�� GetWindow�� ����� ����� ������ ���Ѱ��̴�.
	(���� �� ����� ���丮�� �а� ����带 �ϴ� ������� �ؾ��Ѵ�.)
	�׷��� �� ��ü���� �����Ϳ� ���� �Լ��� ���� ��üor������ ȣ���ϴ� �������
	������ �صξ���.

	�׷��� shared_ptr���ݻ� �߰��� ����ȯ, ������Ʈ �Ҹ��� �Ͼ�� ������ �����.
	�׷��� �������� �����ֱⰡ ���̴� ������ �������̴�.

	Ex)		[ Engine ]		[ Object ]
			Update()	-	Update()		- ��ü �Ҹ�
							FinalUpate()
			Render()	-	Render()
							Editor()		- EditorManager���� ȣ��
	�� �����ε� Update���� ������Ʈ�� �Ҹ��Ű�� �Ʒ��� �ִ� Editor.
	Object�� �����ϰ� ���� Editor�� �����Ǵ� ����� ���� ���� �Ͼ���̴�.
	�׶� ���ٽ����� self = shared_from_this()�� �����ؼ� self->Func()��
	���ְ� �Ǹ� �����ֱⰡ Editor�� ȣ��Ǵ� ���������� ����ǰ� �ȴ�.

	�� ������ ��Ű�� �������� ��� �����̴� ��Ծ����� JobQueue���� ����.
--------------------------------------------------------------------- */


template<typename T>
T* EditorManager::GetWindow()
{
	if (std::is_same_v<T, IEditor>) {
		ASSERT_CRASH("�ȵ�");
		return nullptr;
	}

	T* window = new T;
	EDITOR->PushEditor(window);
	return window;
}