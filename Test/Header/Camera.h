#pragma once

#include "Window.h"
#include "Glfw/glfw3.h"
#include "Glm/glm.hpp"
#include "Glm/gtx/transform.hpp"
#include "Glm/gtc/matrix_transform.hpp"

class Camera {
public:
	void init(glm::vec3 pos, Window* window);
	glm::mat4 getMatrix();

	glm::vec3 getPos();
	glm::vec3 getDirection();

	void setPos(glm::vec3 pos);

	void update();
private:
	void updateMat();

	glm::mat4 m_mat;

	glm::vec3 m_pos;
	glm::vec3 m_direction;
	//glm::vec3 up;

	float horizontalAngle = 0.0f;
	float verticalAngle = 0.0f;
	float initialFoV = 45.0f;

	float speed = 3.0f;
	float mouseSpeed = 0.5f;

	double m_lastTime = glfwGetTime();

	Window* m_window;
};