#pragma once

#include "mcpch.h"
#include "keycodes.h"
#include "mousecodes.h"

namespace Minecraft
{
	class Input
	{
	public:
		inline static bool IsKeyPressed(KeyCode key) { return s_Instance->IsKeyPressedImpl(key); }

		inline static bool IsMouseButtonPressed(MouseCode button) { return s_Instance->IsMouseButtonPressedImpl(button); }

		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); };
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
	public:
		bool IsKeyPressedImpl(KeyCode key);
		bool IsMouseButtonPressedImpl(MouseCode button);
		std::pair<float, float> GetMousePositionImpl();
		float GetMouseXImpl();
		float GetMouseYImpl();
	private:
		static Scope<Input> s_Instance;
	};
}