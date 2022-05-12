#pragma once

#include "utils.h"

enum class MENU_TYPE
{
	NONE = -1,
	SETTING,
	END
};

class MenuEditor : public IEditor
{
public:
	MenuEditor();
	virtual ~MenuEditor();

	virtual void Show() override;
	virtual void End() override;

	MENUITEM("Menu/Editor", MenuEditor, Present);
	static void Present()
	{
		m_pInstance = EDITOR->GetWindow<MenuEditor>();
		m_pInstance->Title = "Editor";
	}


private:
	inline static MenuEditor* m_pInstance;

	array<bool, static_cast<uint32>(MENU_TYPE::END)> m_arrCheck;
};

