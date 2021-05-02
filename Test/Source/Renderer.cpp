#include "Renderer.h"

void ErrorCallback(int error, const char* description) {
	std::cout << "Error: " << description << std::endl;
}

void delay(uint32_t ms)
{
#ifdef _WIN32
	Sleep(ms);
#else
	usleep(ms * 1000);
#endif
}

Renderer::Renderer() {

}

void Renderer::initialize() {

	if (!glfwInit()) {
		std::cout << "Failed to initialize glfw" << std::endl;
		return;
	}

	glfwSetErrorCallback(ErrorCallback);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	mp_window = &m_window;
	m_window.initialize();

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		std::cout << "Failed to initialize glew" << std::endl;
		return;
	}

	std::cout << "Renderer initialized successfuly" << std::endl;

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);


	std::vector<glm::vec3> g_vertex_buffer_data;
	std::vector<glm::vec2> bufer_data_uvs;
	std::vector<glm::vec3> normals;
	
	loadOBJ("cube.obj", g_vertex_buffer_data, bufer_data_uvs, normals);

	// This will identify our vertex buffer
	GLuint vertexbuffer;
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, g_vertex_buffer_data.size() * sizeof(glm::vec3), &g_vertex_buffer_data[0], GL_STATIC_DRAW);


	GLuint programID = LoadShaders("shader.vertex", "shader.fragment");
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);


	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(glm::radians(60.0f), m_window.getWindowSize().x / m_window.getWindowSize().y, 0.1f, 100.0f);

	// Or, for an ortho camera :
	//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices


	// Get a handle for our "MVP" uniform
// Only during the initialisation
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	// Send our transformation to the currently bound shader, in the "MVP" uniform
	// This is done in the main loop since each model will have a different MVP matrix (At least for the M part)

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, bufer_data_uvs.size() * sizeof(glm::vec3), &bufer_data_uvs[0], GL_STATIC_DRAW);


	//GLuint Texture = loadBMP_custom("t.bmp");

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);

	// When MAGnifying the image (no bigger mipmap available), use LINEAR filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// When MINifying the image, use a LINEAR blend of two mipmaps, each filtered LINEARLY too
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// Generate mipmaps, by the way.
	glGenerateMipmap(GL_TEXTURE_2D);


	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	Camera camera;
	camera.init(glm::vec3(0, 2, 5), mp_window);

	glm::mat4 mvp;

	glfwSetInputMode(m_window.getWindow(), GLFW_STICKY_KEYS, GL_TRUE);

	double lastTime = glfwGetTime();
	glfwSwapInterval(1);
	

	while (!glfwWindowShouldClose(m_window.getWindow())) {

		

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(programID, "ourColor");
		glUseProgram(programID);
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		camera.update();
		mvp = Projection * camera.getMatrix() * Model; // Remember, matrix multiplication is the other way around


		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);


		// 1st attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			1,
			2,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 12*3); // Starting from vertex 0; 3 vertices total -> 1 triangle


		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);


		glfwSwapBuffers(m_window.getWindow());
		glfwPollEvents();

		double currentTime = glfwGetTime();
		double elapsedTime = currentTime - lastTime;
		double fps = 1 / elapsedTime;
		std::cout << fps << std::endl;

		//if (elapsedTime < 1 / 60.0f)
			//delay(1 / 60.0f - elapsedTime);

		//std::cout << elapsedTime - 1/60.0f << std::endl;

		lastTime = currentTime;
	}

	glDeleteBuffers(1, &vertexbuffer);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);
}

void Renderer::release() {
	glfwTerminate();
	mp_window = nullptr;

	std::cout << "Renderer released" << std::endl;
}

Renderer::~Renderer() {
	release();
}