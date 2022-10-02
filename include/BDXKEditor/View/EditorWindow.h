﻿#pragma once
#include "BDXKEngine/Framework/ScriptableObject/ScriptableObject.h"
#include "BDXKEngine/Framework/Component/Renderer/RenderEvent.h"

namespace BDXKEditor
{
    using namespace BDXKEngine;

    class EditorWindow : public ScriptableObject, public DrawGUIHandler
    {
    public:
        template <typename TWindow>
        static ObjectPtr<TWindow> Create()
        {
            TWindow window;
            window.SetIsEnabling(false);
            return Instantiate(&window);
        }
        
        void Show();
    protected:
        virtual void OnDrawWindow();
        virtual void OnShow();
    private:
        void OnDrawGUI() override;
    };
}
