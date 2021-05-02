#include "Camera.h"

void Camera::init(glm::vec3 pos, Window* window) {
	m_pos = pos;
	m_window = window;
	updateMat();
}

void Camera::updateMat() {
	m_mat = glm::lookAt(m_pos, m_pos + m_direction, glm::vec3(0, 1, 0));
}

glm::mat4 Camera::getMatrix() {
	updateMat();
	return m_mat;
}

glm::vec3 Camera::getPos() {
	return m_pos;
}

glm::vec3 Camera::getDirection() {
	return m_direction;
}

void Camera::setPos(glm::vec3 pos) {
	m_pos = pos;
	updateMat();
}


void Camera::update() {

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - m_lastTime);

	double mouseX, mouseY;
	glfwGetCursorPos(m_window->getWindow(), &mouseX, &mouseY);
	glfwSetCursorPos(m_window->getWindow(), m_window->getWindowSize().x / 2, m_window->getWindowSize().y / 2);


	horizontalAngle += mouseSpeed * deltaTime * float(m_window->getWindowSize().x / 2 - mouseX);
	verticalAngle += mouseSpeed * deltaTime * float(m_window->getWindowSize().y / 2 - mouseY);

	if (verticalAngle > 1.55f)
		verticalAngle = 1.55f;
	else if (verticalAngle < -1.55f)
		verticalAngle = -1.55f;


	m_direction = glm::vec3(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	glm::vec3 horizontale_direction = glm::vec3(
		sin(horizontalAngle),
		0,
		cos(horizontalAngle)
	);
	
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);

	// Move forward
	if (glfwGetKey(m_window->getWindow(), GLFW_KEY_W) == GLFW_PRESS) {
		m_pos += horizontale_direction * deltaTime * speed;
	}
	// Move backward
	if (glfwGetKey(m_window->getWindow(), GLFW_KEY_S) == GLFW_PRESS) {
		m_pos -= horizontale_direction * deltaTime * speed;
	}
	// Strafe right
	if (glfwGetKey(m_window->getWindow(), GLFW_KEY_D) == GLFW_PRESS) {
		m_pos += right * deltaTime * speed;
	}
	// Strafe left
	if (glfwGetKey(m_window->getWindow(), GLFW_KEY_A) == GLFW_PRESS) {
		m_pos -= right * deltaTime * speed;
	}
	if (glfwGetKey(m_window->getWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		m_pos.y -= deltaTime * speed;
	}
	// Move backward
	if (glfwGetKey(m_window->getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS) {
		m_pos.y += deltaTime * speed;
	}

	std::cout << verticalAngle << std::endl;

	m_lastTime = currentTime;
}