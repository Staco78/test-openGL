#include "Window.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Window::initialize() {

	m_window = glfwCreateWindow(720, 480, "Test", nullptr, nullptr);

	if (!m_window) {
		glfwTerminate();
		std::cout << "Failed to initialize the window" << std::endl;
		return;
	}

	glfwMakeContextCurrent(m_window);
	glfwSetWindowPos(m_window, 600, 300);
	glfwSetWindowSizeCallback(m_window, framebuffer_size_callback);

	std::cout << "Window initialized successfuly" << std::endl;

}

void Window::release() {
	glfwTerminate();
	m_window = nullptr;
	std::cout << "Window released" << std::endl;
}

Window::~Window() {
	release();
}

GLFWwindow* Window::getWindow() {
	return m_window;
}

glm::vec2 Window::getWindowSize() {
	int x;
	int y;
	glfwGetWindowSize(m_window, &x, &y);
	return glm::vec2((float)x, (float)y);
}