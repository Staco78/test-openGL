#include "Renderer2.h"

void ErrorCallback2(int error, const char* description) {
	std::cout << "Error: " << description << std::endl;
}

void delay2(uint32_t ms)
{
#ifdef _WIN32
	Sleep(ms);
#else
	usleep(ms * 1000);
#endif
}

Renderer2::Renderer2() {

}

void Renderer2::initialize() {

	if (!glfwInit()) {
		std::cout << "Failed to initialize glfw" << std::endl;
		return;
	}

	glfwSetErrorCallback(ErrorCallback2);
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

	glfwSwapInterval(1);

	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};


	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//unsigned int EBO;
	//glGenBuffers(1, &EBO);

	// ..:: Initialisation :: ..
// 1. attacher le Vertex Array Object
	glBindVertexArray(VAO);

	// 2. copier les sommets dans un VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 3. copier le tableau d’indices dans un tampon d’éléments
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	

	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	// nous avons juste besoin de lier le VBO, les données du container sont déjà prêtes.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// définit les attributs de sommets (seulement la position)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	glfwSetInputMode(m_window.getWindow(), GLFW_STICKY_KEYS, GL_TRUE);

	glm::vec3 lightPos(0.0f, 0.5f, 2.0f);


	Shader shader("shader.vertex", "shader.fragment");
	shader.use();


	glm::mat4 projection(1.0);
	projection = glm::perspective(glm::radians(45.0f), m_window.getWindowSize().x / m_window.getWindowSize().y, 0.1f, 100.0f);
	shader.setMat4("projection", projection);

	glm::mat4 view(1.0);

	glm::mat4 model(1.0);
	model = glm::translate(model, glm::vec3(0.0, 0.0, 0.0));
	shader.setMat4("model", model);

	shader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
	shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);

	shader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
	shader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
	shader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
	shader.setFloat("material.shininess", 32.0f);

	shader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
	shader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f); // assombri un peu la lumière pour correspondre à la scène
	shader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);



	Shader lightShader("lightShader.vertex", "lightShader.fragment");
	lightShader.use();
	model = glm::mat4(1.0);
	model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(0.2f));
	lightShader.setMat4("model", model);

	lightShader.setMat4("projection", projection);


	bool lineMode = false;
	int cooldown = 0;

	bool depht_test = true;
	int cooldown2 = 0;

	glfwSetInputMode(m_window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	Camera2 camera;
	camera.init(mp_window);


	while (!glfwWindowShouldClose(m_window.getWindow())) {

		lightPos.x = 1.0f + sin(glfwGetTime()) * 2.0f;
		lightPos.y = sin(glfwGetTime() / 2.0f) * 1.0f;


		camera.update();
		shader.use();
		shader.setVec3("viewPos", camera.getPosition());
		shader.setVec3("lightPos", lightPos);

		glm::vec3 lightColor;
		lightColor.x = sin(glfwGetTime() * 2.0f);
		lightColor.y = sin(glfwGetTime() * 0.7f);
		lightColor.z = sin(glfwGetTime() * 1.3f);
		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f); // decrease the influence
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // low influence
		shader.setVec3("light.ambient", ambientColor);
		shader.setVec3("light.diffuse", diffuseColor);



		lightShader.use();
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		lightShader.setMat4("model", model);
		lightShader.setVec3("color", lightColor);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		if (glfwGetKey(m_window.getWindow(), GLFW_KEY_F2) == GLFW_PRESS) {
			if (cooldown == 0) {
				lineMode = !lineMode;
				cooldown = 10;
			}
		}

		if (glfwGetKey(m_window.getWindow(), GLFW_KEY_F3) == GLFW_PRESS) {
			if (cooldown2 == 0) {
				depht_test = !depht_test;
				cooldown2 = 10;
			}
		}

		if (depht_test)
			glEnable(GL_DEPTH_TEST);
		else
			glDisable(GL_DEPTH_TEST);


		if (lineMode)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


		shader.use();
		shader.setMat4("view", camera.getMatrix());

		glBindVertexArray(VAO);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 36);


		lightShader.use();
		lightShader.setMat4("view", camera.getMatrix());

		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(m_window.getWindow());
		glfwPollEvents();

		if (cooldown > 0)
			cooldown--;
		if (cooldown2 > 0)
			cooldown2--;
	}

	
}

void Renderer2::release() {
	glfwTerminate();
	mp_window = nullptr;

	std::cout << "Renderer released" << std::endl;
}

Renderer2::~Renderer2() {
	release();
}
