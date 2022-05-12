#pragma once

#define DEF_EDITOR

#define EDITOR GET_SINGLE(EditorManager)

#define CREATE_EDITOR_FUNC(Func)						\
inline static struct RegisterEditor_##Func				\
{														\
	RegisterEditor_##Func()								\
	{													\
		EDITOR->AddEditor(Func);						\
	}													\
} Register_Editor_##Func;								

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
};

class MenuInfo
{
public:
	bool IsMenuItem() { return m_vecChildMenu.empty(); }
	bool IsMenuBar() { return !m_vecChildMenu.empty(); }

public:
	PRIVATE_PROPERTY(vector<Ref<MenuInfo>>, vecChildMenu);
	PRIVATE_PROPERTY(string, strTitle);
};

class Editor
{
	PRIVATE_PROPERTY(function<void(void)>, FuncOn)
	PRIVATE_PROPERTY(string, Title)
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
	void AddEditor(function<void(void)> p_editor);
	
public:
	void MainMenuBar();

	void RegisterMenuBar(const string& p_title, function<void(void)> p_func);
	Ref<MenuInfo> FindMenuBar(const string& title);
public:
	
	/* ----- Log ------ */
	void ConsoleEditor();
	void Log(const string& log, uint8 state = LOG_STATE::LOG);
	void Clear(uint8 state  = LOG_STATE::LOG | LOG_STATE::ERROR_ | LOG_STATE::WARNING);

private:
	/* ----- Editor ------ */
	ImGuiIO* m_pInfo = nullptr;
	HWND m_hWnd = nullptr;

	vector<function<void(void)>> m_vecFuncEditor;	/* �Ʒ��� ���ǻ��� */

	/* ----- Log ------ */
	uint8 m_eState = LOG_STATE::LOG | LOG_STATE::WARNING | LOG_STATE::ERROR_;
	array<vector<string>, 3> m_arrLogs;

	/* ------ Menu Tree ------ */
	vector<Ref<MenuInfo>> m_vecMenuBar;
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


