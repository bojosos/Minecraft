#include "mcpch.h"
#include "camera.h"
#include "engine/input/input.h"
#include "engine/application.h"
#include <glm/gtx/quaternion.hpp>

namespace Minecraft
{
	Camera::Camera(const glm::mat4& projectionMatrix) : m_ProjectionMatrix(projectionMatrix), m_MouseSensitivity(0.002f), m_Speed(0.04f), m_SprintSpeed(m_Speed * 4.0f), m_MouseWasGrabbed(false)
	{
		Input::SetMouseGrabbed(true);
		Input::SetMouseCursor(CursorType::NO_CURSOR);
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
				m_Yaw += mousePos.x * m_MouseSensitivity;
				m_Pitch += mousePos.y * m_MouseSensitivity;
			}
			m_MouseWasGrabbed = true;

			Input::SetMousePosition(windowCenter);

			glm::quat orientation = GetOrientation();
			m_Rotation = glm::eulerAngles(orientation) * (180.0f / glm::pi<float>());

			glm::vec3 forward = GetForwardDirection(orientation);
			glm::vec3 right = GetRightDirection(orientation);

			glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
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

			glm::mat4 rotation = glm::toMat4(glm::conjugate(orientation));
			glm::mat4 translation = glm::translate(glm::mat4(1.0f), -m_Position);
			m_ViewMatrix = rotation * translation;
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
		float xangle = m_Pitch * 0.5f; // Might have to be negative
		return glm::quat(glm::sin(xangle), 0.0f, 0.0f, glm::cos(xangle)) * glm::quat(0.0f, glm::sin(yangle), 0.0f, glm::cos(yangle));
	}

	glm::vec3 Camera::GetForwardDirection(const glm::quat& orientation) const
	{
		return glm::rotate(orientation, glm::vec3(0.0f, 0.0f, -1.0f));
	}

	glm::vec3 Camera::GetUpDirection(const glm::quat& orientation) const
	{
		return glm::rotate(orientation, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	glm::vec3 Camera::GetRightDirection(const glm::quat& orientation) const
	{
		return glm::rotate(orientation, glm::vec3(1.0f, 0.0f, 0.0f));
	}
}