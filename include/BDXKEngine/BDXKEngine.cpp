﻿#include "BDXKEngine.h"
#include <ranges>
#include "Framework/Scene.h"
#include "Framework/Behavior/BehaviorEvent.h"
#include "Framework/Physics/PhysicsEvent.h"
#include "Framework/Renderer/RenderEvent.h"
#include "Function/Graphics/Graphics.h"
#include "Function/Time/Time.h"
#include "Function/Window/Cursor.h"
#include "Function/Window/Input.h"
#include "Function/Window/Screen.h"
#include "Platform/GUI/GUI.h"
#include "Platform/Phys/Phys.h"
#include "Platform/Resources/Resources.h"


namespace BDXKEngine
{
    void Run(const std::string& sceneName)
    {
        Run([&]
        {
            Scene::Load(sceneName);
        });
    }
    void Run(const std::function<void()>& onStart)
    {
        if (std::setlocale(LC_ALL, "zh-CN.UTF-8") == nullptr) // NOLINT(concurrency-mt-unsafe)
            throw std::exception("设置本地化失败");

        //平台层
        Window window{L"BDXKEngine"};
        GL::Initialize(&window);
        GUI::Initialize(&window);
        Phys::Initialize(&window);
        //框架层
        Graphics::Initialize(&window);
        Screen::Initialize(&window);
        Cursor::Initialize(&window);
        Input::Initialize(&window);
        Time::Initialize(&window);
        PhysicsEvent::Initialize(&window);
        BehaviorEvent::Initialize(&window);
        RenderEvent::Initialize(&window);

        //正式开始
        {
            onStart();
            window.Show();
        }

        std::vector<ObjectPtrBase> objectPtrBases = {};
        for (const auto& item : Object::GetObjects() | std::ranges::views::values)
            objectPtrBases.emplace_back(item);
        for (const auto& item : objectPtrBases)
            Object::DestroyImmediate(item);

        // Debug::LogError("系统回收检查");
        // BDXKObject::DebugObjectCount();
        // ObjectPtrBase::PrintRefCountMap();
        // BehaviorManager::DebugHandlersCount();
    }
}
