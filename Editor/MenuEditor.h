#pragma once

#include "utils.h"

enum class MENU_TYPE
{
	NONE = -1,
	SETTING,
	END
};

class MenuEditor
{
public:
	MenuEditor();
	virtual ~MenuEditor();

	CREATE_EDITOR_FUNC(Present)
	static void Present();


	static void On()
	{
		ImGui::Begin("Text");
		ImGui::End();
	}

private:
	array<bool, static_cast<uint32>(MENU_TYPE::END)> m_arrCheck;
};

