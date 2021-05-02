#pragma once

#include "Glfw/glfw3.h"
#include "Glm/glm.hpp"
#include "Glm/vec2.hpp"
#include <iostream>

class Window {
public:
	~Window();

	void initialize();
	void release();
	glm::vec2 getWindowSize();

	GLFWwindow* getWindow();

private:
	GLFWwindow* m_window = nullptr;
};