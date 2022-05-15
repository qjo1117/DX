#include "pch.h"
#include "SceneObjectEditor.h"
#include "GameObject.h"

SceneObjectEditor::~SceneObjectEditor()
{
}

void SceneObjectEditor::Show()
{
	if (m_pScene == nullptr) {
		m_pScene = GET_SINGLE(SceneManager)->GetCurrentScene();
		if (m_pScene == nullptr) {
			return;
		}
	}

	for (auto& obj : m_pScene->GetGameObjects()) {
		bool enable = obj->GetIsEnable();
		if (ImGui::Checkbox(Utils::Wstr2Str(obj->GetName()).c_str(), &enable)) {
			// TODO : ���ý� ��� ������ ����
		}
		obj->SetIsEnable(enable);
	}
}

void SceneObjectEditor::End()
{
	m_pScene = nullptr;
}
