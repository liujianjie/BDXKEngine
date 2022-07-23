#pragma once
#include "Graphics.h"
#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "Renderer.h"
#include "Screen.h"
#include "Light.h"

namespace BDXKEngine {
	enum class ClearFlags {
		Not,
		Color,
		Skybox,
	};

	enum class Projection {
		Orthographic,
		Perspective
	};

	class Camera :public Component, public RenderObjectEvent, RendererEditor, LightEditor
	{
	public:
		Camera();

		void SetClearFlags(ClearFlags clearFlags);
		void SetBackground(Color color);
		void SetNearClipPlane(float distance);
		void SetFarClipPlane(float distance);
	private:
		ClearFlags clearFlags = ClearFlags::Color;
		Projection projection = Projection::Orthographic;// TODO
		Color background = Color::gray;
		float nearClipPlane = 0.3f;
		float farClipPlane = 1000;
		float fieldOfView = 60;
		float size = 1;// TODO

		ObjectPtr<Transform> transform{};

		void OnAwake() override
		{
			Component::OnAwake();

			transform = GetGameObject()->GetTransform();
		}

		void OnRenderObject()override;
	};
}
