﻿#include "SceneWindow.h"
#include "CameraController.h"
#include "BDXKEngine/Framework/Scene.h"
#include "BDXKEngine/Function/Time/Time.h"
#include "BDXKEngine/Platform/GUI/GUI.h"
#include "ImGuizmo/ImGuizmo.h"

namespace BDXKEditor
{
    void SceneWindow::SetTarget(const ObjectPtr<GameObject>& target)
    {
        this->target = target;
    }

    void SceneWindow::OnAwake()
    {
        const ObjectPtr<GameObject> editorCameraGameObject = Creation::CreateCamera(":SceneWindow");

        camera = editorCameraGameObject->GetComponent<Camera>();
        cameraTexture = Texture2D::Create(960, 540, TextureFormat::B8G8R8A8_UNORM);
        cameraController = Component::Create<CameraController>(editorCameraGameObject);
        viewSize = {960, 540};

        camera->SetRenderTarget(cameraTexture);
    }

    void SceneWindow::OnGUI()
    {
        //更新渲染纹理大小
        if (cameraTexture->GetSize() != viewSize && viewSize.x * viewSize.y > 0)
        {
            cameraTexture = Texture2D::Create(viewSize.GetXInt(), viewSize.GetYInt(), TextureFormat::B8G8R8A8_UNORM);
            camera->SetRenderTarget(cameraTexture);
        }

        const Vector2 windowMin = ImGui::GetWindowContentRegionMin();
        const Vector2 windowMax = ImGui::GetWindowContentRegionMax();
        const Vector2 viewPosition = Vector2{ImGui::GetWindowPos()} + windowMin;
        viewSize = windowMax - windowMin;

        //显示相机画面
        const Vector2 cursorPos = ImGui::GetCursorPos();
        ImGui::Image(
            GUI::GetImTextureID(cameraTexture),
            cameraTexture->GetSize()
        );
        ImGui::SetCursorPos(cursorPos);
        //手柄选项
        static constexpr char optionsName[4][10] = {"Bounds", "Position", "Rotation", "Scale"};
        static constexpr ImGuizmo::OPERATION options[] = {ImGuizmo::BOUNDS, ImGuizmo::TRANSLATE, ImGuizmo::ROTATE, ImGuizmo::SCALE};
        const float width = ImGui::GetContentRegionAvail().x / 4 - 10;
        static int handleMode = 1;
        for (int i = 0; i < 4; i++)
        {
            ImGui::SetCursorPos(cursorPos + Vector2{(width + 10) * static_cast<float>(i), 0.0f});
            if (ImGui::Selectable(optionsName[i], handleMode == i, 0, Vector2{width, 0.0f}))
                handleMode = i;
        }
        //帧率信息
        ImGui::Text(
            "Rate %.3f ms/frame (%.1f FPS)",
            static_cast<double>(Time::GetDeltaTime() * 1000.0f),
            static_cast<double>(1.0f / Time::GetDeltaTime())
        );

        cameraController->SetIsEnabling(ImGui::IsWindowHovered());
        if (ImGui::IsWindowHovered() && cameraController->IsControlling() == false)
        {
            if (ImGui::IsKeyDown(ImGuiKey_Q))handleMode = 0;
            if (ImGui::IsKeyDown(ImGuiKey_W))handleMode = 1;
            if (ImGui::IsKeyDown(ImGuiKey_E))handleMode = 2;
            if (ImGui::IsKeyDown(ImGuiKey_R))handleMode = 3;
        }
        if (GUI::IsDockTabVisible())
        {
            //绘制小物件
            CameraInfo cameraInfo = camera->GetCameraInfo();
            ImGuizmo::SetRect(viewPosition.x, viewPosition.y, viewSize.x, viewSize.y);
            ImGuizmo::SetOrthographic(false);
            //绘制网格
            {
                Matrix4x4 objectToWorld = Matrix4x4::identity;
                ImGuizmo::DrawGrid(
                    reinterpret_cast<float*>(&cameraInfo.worldToView),
                    reinterpret_cast<float*>(&cameraInfo.viewToClip),
                    reinterpret_cast<float*>(&objectToWorld),
                    10
                );
            }
            //绘制手柄
            if (target.IsNotNull())
            {
                Matrix4x4 objectToWorld = target->GetLocalToWorldMatrix();
                Manipulate(
                    reinterpret_cast<float*>(&cameraInfo.worldToView),
                    reinterpret_cast<float*>(&cameraInfo.viewToClip),
                    options[handleMode], ImGuizmo::LOCAL,
                    reinterpret_cast<float*>(&objectToWorld)
                );

                Vector3 position;
                Vector3 rotation;
                Vector3 scale;
                ObjectPtr<GameObject> parent = target->GetParent();
                Matrix4x4::DecomposeTRS(
                    parent.IsNull() ? objectToWorld : parent->GetWorldToLocalMatrix() * objectToWorld,
                    position, rotation, scale
                );
                target->SetLocalPosition(position);
                target->SetLocalEulerAngles(rotation);
                target->SetLocalScale(scale);
            }
        }
    }
}
