﻿#include "Editor.h"

namespace BDXKEditor
{
    std::unordered_map<Type, Editor*> Editor::editors = {};

    Editor defaultEditor;
    Editor* Editor::GetEditor(const Reflective& reflective)
    {
        const Type type = reflective.GetType();
        if (editors.contains(type))
            return editors[type];
        for (auto& func : getEditorFallback)
            if (Editor* editor = func(reflective); editor != nullptr)
                return editor;

        return &defaultEditor;
    }
    void Editor::AddEditorFallback(const std::function<Editor*(const Reflective&)>& getEditorFallback)
    {
        Editor::getEditorFallback.push_back(getEditorFallback);
    }
    const ObjectPtrBase& Editor::GetTarget() const
    {
        return target;
    }
    Transferer* Editor::GetGUITransferer() const
    {
        return gui;
    }
    void Editor::SetTarget(const ObjectPtrBase& target)
    {
        this->target = target;
    }
    void Editor::SetGui(Transferer* gui)
    {
        this->gui = gui;
    }

    void Editor::DrawInspectorGUI()
    {
        OnInspectorGUI();
    }
    void Editor::DrawSceneGUI()
    {
        OnSceneGUI();
    }
    void Editor::OnInspectorGUI()
    {
        target.ToObjectBase()->Transfer(*gui);
    }
    void Editor::OnSceneGUI()
    {
    }
}
