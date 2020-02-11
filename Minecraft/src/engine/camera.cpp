#include "mcpch.h"
#include "camera.h"
#include "engine/input/input.h"
#include "engine/application.h"
#include <glm/gtx/quaternion.hpp>

namespace Minecraft
{
	Camera::Camera(const glm::mat4& projectionMatrix) : m_ProjectionMatrix(projectionMatrix), m_MouseSensitivity(0.002f), m_Speed(0.04f), m_SprintSpeed(m_Speed * 4.0f), m_MouseWasGrabbed(false)
	{
		m_ViewMatrix = glm::mat4(1.0f);
		m_Position = { 0.0f, 0.0f, -0.0f };
		m_Rotation = { 0.0f, 0.0f, 0.0f };

		m_Yaw = 0.0f;
		m_Pitch = 0.0f;
	}

	Camera::~Camera()
	{

	}

	void Camera::Focus()
	{
		Input::SetMouseGrabbed(true);
		Input::SetMouseCursor(CursorType::NO_CURSOR);
	}

	void Camera::Update()
	{
		glm::vec2 windowSize = Application::Get().GetWindowSize();
		glm::vec2 windowCenter = glm::vec2((float)(int32_t)(windowSize.x / 2.0f), (float)(int32_t)(windowSize.y / 2.0f));

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
			mousePos.x -= windowCenter.x;
			mousePos.y -= windowCenter.y;

			if (m_MouseWasGrabbed)
			{
				m_Rotation.y += mousePos.x * m_MouseSensitivity * 60.0f;
				m_Rotation.x += mousePos.y * m_MouseSensitivity * 60.0f;
			}
			if (m_Rotation.x < -80.0f) {
				m_Rotation.x = -79.9f;
			}
			else if (m_Rotation.x > 85.0f) {
				m_Rotation.x = 84.9f;
			}
			m_MouseWasGrabbed = true;

			Input::SetMousePosition(windowCenter);
			
			glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
			glm::vec3 forward = GetForwardDirection(m_Rotation);
			glm::vec3 right = GetRightDirection(m_Rotation);
			
			float speed = Input::IsKeyPressed(KeyCode::LeftControl) ? m_SprintSpeed : m_Speed;

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
			m_ViewMatrix = glm::rotate(m_ViewMatrix, glm::radians(m_Rotation.x), { 1, 0, 0 });
			m_ViewMatrix = glm::rotate(m_ViewMatrix, glm::radians(m_Rotation.y), { 0, 1, 0 });
			m_ViewMatrix = glm::rotate(m_ViewMatrix, glm::radians(m_Rotation.z), { 0, 0, 1 });

			m_ViewMatrix = glm::translate(m_ViewMatrix, -m_Position);
		}
		if (Input::IsKeyPressed(KeyCode::Escape))
		{
			Input::SetMouseGrabbed(false);
			Input::SetMouseCursor(CursorType::POINTER);
			m_MouseWasGrabbed = false;
		}
	}

	glm::quat Camera::GetOrientation() const
	{
		float yangle = m_Yaw * 0.5f;
		float xangle = m_Pitch * 0.5f;

		return glm::quat(glm::sin(xangle), 0.0f, 0.0f, glm::cos(xangle)) * glm::quat(0.0f, glm::sin(yangle), 0.0f, glm::cos(yangle));
	}

	glm::vec3 Camera::GetForwardDirection(const glm::vec3& rotation) const
	{
		float yaw = glm::radians(rotation.y + 90);
		float pitch = glm::radians(rotation.x);
		float x = glm::cos(yaw) * glm::cos(pitch);
		float y = glm::sin(pitch);
		float z = glm::cos(pitch) * glm::sin(yaw);

		return { -x,-y,-z };
	}

	glm::vec3 Camera::GetRightDirection(const glm::vec3& rotation) const
	{
		float yaw = glm::radians(rotation.y);
		float x = glm::cos(yaw);
		float y = 0;
		float z = glm::sin(yaw);

		return { x, y, z };
	}
};