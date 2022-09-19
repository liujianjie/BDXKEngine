#pragma once
#include <vector>
#include "Window.h"
#include "GL2D.h"
#include "CameraEvent.h"

namespace BDXKEngine {
	class Renderer;
	class RendererManager :protected GL
	{
		friend Renderer;
	public:
		static RendererManager* Initialize(Window* window);
	protected:
		static std::vector<ObjectPtr<Renderer>>& GetRenderers();
		static std::vector<ObjectPtr<Renderer>> GetRenderersQueue();
	private:
		static std::vector<ObjectPtr<Renderer>> renderers;//��Renderer����
	};
}
