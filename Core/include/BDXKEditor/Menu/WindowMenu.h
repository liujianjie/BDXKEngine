﻿#pragma once
#include "Core/Menu.h"

namespace BDXKEditor
{
    class WindowMenu
    {
    public:
        static void CreateRenderSettingsWindow();
        static void CreateGameWindow();
    private:
        CustomMenu("Window/Scene/RenderSettings", CreateRenderSettingsWindow)
        CustomMenu("Window/Editor/Game", CreateGameWindow)
    };
}
