#pragma once

#include "Scene.h"
#include "EditorManager.h"

class SceneObjectEditor :
	public IEditor
{
public:
	virtual ~SceneObjectEditor();
						
	MENUITEM("Menu/Object_List", SceneObjectEditor, Present);
	static void Present()
	{
		m_pInstance = EDITOR->GetWindow<SceneObjectEditor>();
		m_pInstance->Title = "OBJECT_LIST";
	}

	virtual void Show() override;
	virtual void End() override;

private:
	Ref<class Scene> m_pScene;

public:
	inline static SceneObjectEditor* m_pInstance;
};

