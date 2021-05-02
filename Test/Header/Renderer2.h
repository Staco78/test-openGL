#pragma once
#include "Glew/glew.h"
#include <Glm/glm.hpp>
#include <Glm/gtc/matrix_transform.hpp>
#include <Glm/gtc/type_ptr.hpp>

#include "Window.h"
#include "Shader.h"
#include "Camera2.h"

#include "stb_image.h"

//#define STB_IMAGE_IMPL EMENTATION
//#include "stb_image.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

class Renderer2 {
public:
	Renderer2();
	~Renderer2();
	void initialize();
	void release();
private:

	Window m_window;
	Window* mp_window = nullptr;

	bool firstMouse = true;
	

	double lastX;
	double lastY;

	float yaw;
	float pitch;
};