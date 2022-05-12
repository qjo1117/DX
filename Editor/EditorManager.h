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

	vector<function<void(void)>> m_vecFuncEditor;	/* 아래에 주의사항 */

	/* ----- Log ------ */
	uint8 m_eState = LOG_STATE::LOG | LOG_STATE::WARNING | LOG_STATE::ERROR_;
	array<vector<string>, 3> m_arrLogs;

	/* ------ Menu Tree ------ */
	vector<Ref<MenuInfo>> m_vecMenuBar;
};

/* ---------------------------------------------------------------------
	가끔씩 까먹으닌깐 적어두자
	shared_ptr 공유라는 개념을 쓰는동안 Object내부로 함수를 호출하는 경우가 잦다.
	상속으로 해둔 것은 그냥 DX9 수업 자체적으로 사람들에게 보여주기도 직관적이고
	보여지는 것도 클래스 다이어그램으로 표현이 가능하기때문이다.
	
	하지만 Editor를 넣는 구간에는 살짝 애매한 점이 생긴다.
	Unity처럼 GetWindow로 만드는 방식은 생각을 안한것이다.
	(물론 저 방식은 디렉토리를 읽고 재빌드를 하는 방식으로 해야한다.)
	그래서 각 객체마다 에디터에 대한 함수를 갖고 객체or씬에서 호출하는 방식으로
	구현을 해두엇다.

	그러면 shared_ptr성격상 중간에 씬전환, 오브젝트 소멸이 일어날때 문제가 생긴다.
	그럴때 에디터의 생명주기가 꼬이는 현상이 잇을것이다.

	Ex)		[ Engine ]		[ Object ]
			Update()	-	Update()		- 객체 소멸
							FinalUpate()
			Render()	-	Render()
							Editor()		- EditorManager에서 호출
	이 순서인데 Update에서 오브젝트를 소멸시키면 아래에 있는 Editor.
	Object를 참조하고 있을 Editor가 에러또는 복사로 인해 릭이 일어날것이다.
	그때 람다식으로 self = shared_from_this()로 지정해서 self->Func()을
	해주게 되면 생명주기가 Editor가 호출되는 시점까지는 보장되게 된다.

	이 개념은 루키스 서버에서 배운 내용이니 까먹었으면 JobQueue쪽을 보자.
--------------------------------------------------------------------- */


