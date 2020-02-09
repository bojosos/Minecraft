#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Minecraft
{
	class Camera
	{
	public:
		Camera(const glm::mat4& projectionMatrix);
		~Camera();

		void Focus();
		void Update();

		inline const glm::vec3& GetPosition() const { return m_Position; }
		inline void SetPosition(const glm::vec3& position) { m_Position = position; }

		inline const glm::vec3& GetRotation() const { return m_Rotation; }
		inline void SetRotation(const glm::vec3& rotation) { m_Rotation = rotation; }

		inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		inline void SetProjectionMatrix(const glm::mat4& matrix) { m_ProjectionMatrix = matrix; }

		inline void Translate(const glm::vec3& translation) { m_Position += translation; }
		inline void Rotate(const glm::vec3& rotation) { m_Rotation += rotation; }

		inline void Translate(float x, float y, float z) { m_Position += glm::vec3(x, y, z); }
		inline void Rotate(float x, float y, float z) { m_Rotation += glm::vec3(x, y, z); }

		inline const glm::mat4& GetViewMatrix() { return m_ViewMatrix; }

	private:
		glm::vec3 up = { 0.0f,1.0f,0.0f };

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;

		glm::vec3 m_Position;
		glm::vec3 m_Rotation;

		float m_MouseSensitivity;
		float m_Speed, m_SprintSpeed;
		float m_Pitch, m_Yaw;
		bool m_MouseWasGrabbed;

	private:
		glm::quat GetOrientation() const;
		glm::vec3 GetForwardDirection(const glm::vec3& rotation) const;
		//glm::vec3 Camera::GetUpDirection(const glm::quat& orientation) const;
		glm::vec3 Camera::GetRightDirection(const glm::vec3& rotation) const;
	};

}