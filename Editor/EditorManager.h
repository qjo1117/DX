#pragma once

#include "../Engine/EnginePch.h"

#define DEF_EDITOR

#define EDITOR GET_SINGLE(EditorManager)

/* --------- Attribute 흉내내기 --------- */
			

#define MENUITEM(Title, Class, Func)					\
inline static struct Register_##Class_##Func			\
{														\
	Register_##Class_##Func()							\
	{													\
		EDITOR->RegisterMenuBar(Title, Class::Func);	\
	}													\
} Register_##Class_##Func					

/* -----------------------------------------------------------------
					Attribute 흉내내기 설명서
	속성을 찾다가 property에 대한 정보도 알아가고 코드중에 리플렉션를
	만들었다는 자료를 보게 되었습니다.

	생각 : Attribute든 뭐든 함수를 한번만이라도 호출하게 할 수 있으면
	MenuItem()에 대한 작업을 구현할 수 있을 것이다.
	그래서 자료를 찾을때도 속성에서 함수호출 가능여부 위주로 찾았습니다.

	Reflection 예제를 보다가 생각한 것인데 언리얼에서는 매크로를
	자주 이용했습니다.
	잘 토대로 생각해보니 굳이 속성을 찾을 필요없이 매크로를 속성처럼
	사용하는 것은 어떨까? 라는 생각이 들면서 매크로에 있는
	static struct A { A() {} } a(); 호출 방식을 눈에 띄였습니다.
	static인건 마음에 안들지만 생성자 '함수 호출'이 가능하다는 생각을
	할 수 있었습니다.

	그 뒤로는 간단하게 구현했습니다.
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


template<typename T>
T* EditorManager::GetWindow()
{
	if (std::is_same_v<T, IEditor>) {
		ASSERT_CRASH("안됨");
		return nullptr;
	}

	T* window = new T;
	EDITOR->PushEditor(window);
	return window;
}