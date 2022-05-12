#pragma once

#include "DirectoryManager.h"

class DirectoryEditor : public IEditor
{
public:

	MENUITEM("Menu/Directory", DirectoryEditor, Present);
	static void Present()
	{
		m_pInstance = EDITOR->GetWindow<DirectoryEditor>();
		m_pInstance->Title = "Directory";
	}

	virtual void Show() override;
	virtual void End() override;

	void Ref_TreeNode(Ref<FileInfo> info);

private:
	inline static DirectoryEditor* m_pInstance;
};

