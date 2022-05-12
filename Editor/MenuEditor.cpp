#include "pch.h"
#include "MenuEditor.h"
#include "Engine.h"

MenuEditor::MenuEditor() 
{
	for (auto& check : m_arrCheck) {
		check = false;
	}
}

MenuEditor::~MenuEditor()
{

}

void MenuEditor::Show()
{
	ImGui::Button("Hello");
}

void MenuEditor::End()
{
	
}
