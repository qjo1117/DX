#pragma once

#include "Scene.h"

class SceneObjectEditor
{
public:
	virtual void Present();

private:
	Ref<class Scene> m_pScene;

	bool m_bEable = false;
};

