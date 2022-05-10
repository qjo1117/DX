#pragma once



#define EDITOR GET_SINGLE(EditorManager)

enum LOG_STATE : uint8
{
	NONE = 0,
	LOG		= 1 << 1,
	WARNING = 1 << 2,
	ERROR_	= 1 << 3,
	LOG_STATE_END
};

#define LOG(log, state) EDITOR->Log(log, state)

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
	/* ----- Log ------ */
	void ConsoleEditor();
	void Log(const string& log, uint8 state = LOG_STATE::LOG);
	void Clear(uint8 state  = LOG_STATE::LOG | LOG_STATE::ERROR_ | LOG_STATE::WARNING);

private:
	/* ----- Editor ------ */
	ImGuiIO* m_pInfo = nullptr;
	HWND m_hWnd = nullptr;

	vector<function<void(void)>> m_vecEditor;

	/* ----- Log ------ */
	uint8 m_eState = LOG_STATE::LOG | LOG_STATE::WARNING | LOG_STATE::ERROR_;
	array<vector<string>, 3> m_arrLogs;
};
