/*

		Copyright 2024 Etay Meiri

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

	This camera implementation is based on the "3D Graphics Rendering Cookbook"
*/

#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

static bool constexpr CAMERA_LEFT_HANDED = false;

struct MouseState {
	glm::vec2 m_pos = glm::vec2(0.0f);
	bool m_pressedLeft = false;
};


class CameraPositioner {

public:
	
	virtual glm::mat4 GetViewMatrix() const = 0;
	
	virtual glm::vec3 GetPosition() const = 0;
};

class Camera {
public:

	Camera(CameraPositioner& Positioner) : m_positioner(Positioner) {}

	glm::mat4 GetViewMatrix() const { return m_positioner.GetViewMatrix(); }

	glm::vec3 GetPosition() const { return m_positioner.GetPosition(); }

private:

	CameraPositioner& m_positioner;
};


class CameraPositionerFirstPerson : public CameraPositioner {
public:
	struct Movement {
		bool Forward = false;
		bool Backward = false;
		bool Left = false;
		bool Right = false;
		bool Up = false;
		bool Down = false;
		bool FastSpeed = false;
	};

	Movement m_movement;
	float m_mouseSpeed = 4.0f;
	float m_acceleration = 150.0f;
	float m_damping = 0.2f;
	float m_maxSpeed = 10.0f;
	float m_fastCoef = 10.0f;

	CameraPositionerFirstPerson() {}
	CameraPositionerFirstPerson(const glm::vec3& Pos, const glm::vec3& Target, const glm::vec3& Up);

	void Update(float dt, const glm::vec2& MousePos, bool MousePressed);

	virtual glm::mat4 GetViewMatrix() const;

	virtual glm::vec3 GetPosition() const { return m_cameraPos; }

	void SetPosition(const glm::vec3& Pos) { m_cameraPos = Pos; }

	void SetUpVector(const glm::vec3& Up);

	void ResetMousePosition(const glm::vec2& Pos) { m_mousePos = Pos; }

private:

	glm::vec3 CalcAcceleration();
	void CalcMoveSpeed(float dt);
	void CalcCameraOrientation(const glm::vec2& MousePos);

	glm::vec2 m_mousePos = glm::vec2(0.0f);
	glm::vec3 m_cameraPos = glm::vec3(0.0f);
	glm::quat m_cameraOrientation = glm::quat(glm::vec3(0.0f));
	glm::vec3 m_moveSpeed = glm::vec3(0.0f);
};
