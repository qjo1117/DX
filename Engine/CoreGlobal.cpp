#include "pch.h"
#include "CoreGlobal.h"
#include "../Editor/EditorManager.h"

EditorManager*	GEditorMgr = nullptr;

class CoreGlobal
{
public:
	CoreGlobal()
	{
		GET_SINGLE(EditorManager);

	}

	~CoreGlobal()
	{
		
	}
} GCoreGlobal;