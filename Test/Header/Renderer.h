#pragma once
#include "Glew/glew.h"
#include "Glm/glm.hpp"
#include "Glm/gtx/transform.hpp"
#include "Glm/gtc/matrix_transform.hpp"

#include "Window.h"
#include "LoadShader.h"
#include "LoadTexture.h"
#include "Camera.h"
#include "objLoader.h"

//#define STB_IMAGE_IMPL EMENTATION
//#include "stb_image.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

class Renderer {
public:
	Renderer();
	~Renderer();
	void initialize();
	void release();

private:
	
	Window m_window;
	Window* mp_window = nullptr;
};