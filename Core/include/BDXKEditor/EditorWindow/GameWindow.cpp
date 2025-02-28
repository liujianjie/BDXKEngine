﻿#include "GameWindow.h"
#include <algorithm>
#include "BDXKEngine/Function/Window/Input.h"
#include "BDXKEngine/Platform/GUI/GUI.h"

namespace BDXKEditor
{
    std::unordered_map<ID, bool> GameWindow::isWindowHovered = {};

    void GameWindow::OnGUI()
    {
        if (std::ranges::all_of(Camera::GetCameraQueue(), [](Camera* camera) { return camera->GetRenderTarget().IsNotNull(); }))
        {
            ImGui::SetCursorPosY(ImGui::GetContentRegionAvail().y / 2);
            ImGui::Text("No Camera Direct Render To Screen");
            return;
        }

        isWindowHovered[GetInstanceID()] = ImGui::IsWindowHovered();
        Input::SetIsEnabling(std::ranges::any_of(isWindowHovered, [](const std::pair<const int, bool>& item) { return item.second; }));

        const Vector2 windowMin = ImGui::GetWindowContentRegionMin();
        const Vector2 windowMax = ImGui::GetWindowContentRegionMax();
        const Vector2 viewSize = windowMax - windowMin;
        const Vector2 canvasSize = RenderEvent::GetCameraCanvas()->GetSize();
        const float factor = viewSize.x / viewSize.y > canvasSize.x / canvasSize.y
                                 ? viewSize.y / canvasSize.y
                                 : viewSize.x / canvasSize.x;
        ImGui::SetCursorPos(windowMin + viewSize / 2 - canvasSize * factor * 0.5f);
        ImGui::Image(
            GUI::GetImTextureID(RenderEvent::GetCameraCanvas()),
            canvasSize * factor
        );
    }
}
