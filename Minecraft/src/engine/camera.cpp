#include "mcpch.h"
#include "camera.h"
#include "engine/input/input.h"
#include "engine/application.h"
#include <glm/gtx/quaternion.hpp>

namespace Minecraft
{
	Camera::Camera(const glm::mat4& projectionMatrix) : m_ProjectionMatrix(projectionMatrix), m_MouseSensitivity(0.002f), m_RotationSpeed(60.0f), m_Speed(0.04f), m_SprintSpeed(m_Speed * 6.0f), m_MouseWasGrabbed(false)
	{
		m_ViewMatrix = glm::mat4(1.0f);
		m_Rotation = { 0.0f, 0.0f, 0.0f };

		m_Yaw = 0.0f;
		m_Pitch = 0.0f;
		m_Frustum = CreateRef<ViewFrustum>();
	}

	Camera::~Camera()
	{

	}

	void Camera::Focus()
	{
		Input::SetMouseGrabbed(true);
		Input::SetMouseCursor(CursorType::NO_CURSOR);
	}

	void Camera::Update(Timestep ts)
	{
#ifndef MC_WEB
		glm::vec2 windowSize = Application::Get().GetWindowSize();
		glm::vec2 windowCenter = glm::vec2((float)(int32_t)(windowSize.x / 2.0f), (float)(int32_t)(windowSize.y / 2.0f));
#endif
		if (Input::IsMouseButtonPressed(MouseCode::ButtonRight))
		{
			if (!Input::IsMouseGrabbed())
			{
				Input::SetMouseGrabbed(true);
				Input::SetMouseCursor(CursorType::NO_CURSOR);
			}
		}

		if (Input::IsMouseGrabbed())
		{
			glm::vec2 mousePos = Input::GetMousePosition();
#ifdef MC_WEB
			mousePos.x -= lastPos.x;
			mousePos.y -= lastPos.y;
			lastPos = Input::GetMousePosition();
#else
			mousePos.x -= windowCenter.x;
			mousePos.y -= windowCenter.y;
#endif
			if (m_MouseWasGrabbed)
			{
				m_Rotation.y += mousePos.x * m_MouseSensitivity*60;// *m_RotationSpeed;// *(float)ts;
				m_Rotation.x += mousePos.y * m_MouseSensitivity*60;// *m_RotationSpeed;// *(float)ts;
			}
			/*
			if (m_Rotation.x < -80.0f) {
				m_Rotation.x = -79.9f;
			}
			else if (m_Rotation.x > 85.0f) {
				m_Rotation.x = 84.9f;
			}*/
			m_MouseWasGrabbed = true;

#ifndef MC_WEB
			Input::SetMousePosition(windowCenter);
#endif

			glm::vec3 forward = GetForwardDirection();
			glm::vec3 right = GetRightDirection();
			
			float speed = (Input::IsKeyPressed(KeyCode::LeftControl) ? m_SprintSpeed : m_Speed);// *(float)ts;

			if (Input::IsKeyPressed(KeyCode::W))
				m_Position += forward * speed;
			if (Input::IsKeyPressed(KeyCode::S))
				m_Position -= forward * speed;
			if (Input::IsKeyPressed(KeyCode::D))
				m_Position += right * speed;
			if (Input::IsKeyPressed(KeyCode::A))
				m_Position -= right * speed;
			if (Input::IsKeyPressed(KeyCode::Space))
				m_Position += up * speed;
			if (Input::IsKeyPressed(KeyCode::LeftShift))
				m_Position -= up * speed;

			m_ViewMatrix = glm::mat4(1.0f);

			m_ViewMatrix = glm::rotate(m_ViewMatrix, glm::radians(m_Rotation.x), { 1.0f, 0.0f, 0.0f });
			m_ViewMatrix = glm::rotate(m_ViewMatrix, glm::radians(m_Rotation.y), { 0.0f, 1.0f, 0.0f });
			m_ViewMatrix = glm::rotate(m_ViewMatrix, glm::radians(m_Rotation.z), { 0.0f, 0.0f, 1.0f });

			m_ViewMatrix = glm::translate(m_ViewMatrix, -m_Position);
		}
		if (Input::IsKeyPressed(KeyCode::Escape))
		{
			Input::SetMouseGrabbed(false);
			Input::SetMouseCursor(CursorType::POINTER);
			m_MouseWasGrabbed = false;
		}

		m_Frustum->Update(m_ProjectionMatrix * m_ViewMatrix);
	}

};