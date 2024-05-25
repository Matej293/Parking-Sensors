#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

GLfloat carVertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
	-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
	 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
	 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
};

GLfloat frontSensorVertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.25f, 0.5f, 0.0f,		1.0f, 1.0f, 1.0f,	0.0f, 0.0f, // Lower left corner
	-0.25f, 1.0f, 0.0f,		1.0f, 1.0f, 1.0f,	0.0f, 1.0f, // Upper left corner
	 0.25f, 1.0f, 0.0f,		1.0f, 1.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
	 0.25f, 0.5f, 0.0f,		1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
};

GLfloat backSensorVertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.25f, -1.0f, 0.0f,	1.0f, 1.0f, 1.0f,	0.0f, 0.0f, // Lower left corner
	-0.25f, -0.5f, 0.0f,	1.0f, 1.0f, 1.0f,	0.0f, 1.0f, // Upper left corner
	 0.25f, -0.5f, 0.0f,	1.0f, 1.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
	 0.25f, -1.0f, 0.0f,	1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
};

// Indices for vertices order
GLuint indices[] =
{
	0, 2, 1,
	0, 3, 2
};

// Function to setup VAO, VBO, and EBO for given vertices and indices
static void setupVAO(VAO& vao, VBO& vbo, EBO& ebo, GLfloat* vertices, size_t verticesSize, GLuint* indices, size_t indicesSize) {
	vao.Bind();
	vbo = VBO(vertices, verticesSize);
	ebo = EBO(indices, indicesSize);
	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();
}

static void RenderCar(VAO& VAO1, Texture car)
{
	VAO1.Bind();
	car.Bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	car.Unbind();
	VAO1.Unbind();
}

static void RenderFrontSensors(Shader& shader, VAO& VAO2, Texture frontCarSensor[], int i)
{
	int activeTextureSet = 0;
	VAO2.Bind();
	glUniform1i(glGetUniformLocation(shader.ID, "activeTextureSet"), activeTextureSet);

	frontCarSensor[i].Bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	frontCarSensor[i].Unbind();
	VAO2.Unbind();
}

static void RenderBackSensors(Shader& shader, VAO& VAO3, Texture backCarSensor[], int i)
{
	int activeTextureSet = 1;
	VAO3.Bind();
	glUniform1i(glGetUniformLocation(shader.ID, "activeTextureSet"), activeTextureSet);

	backCarSensor[i].Bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	backCarSensor[i].Unbind();
	VAO3.Unbind();
}

int main()
{
	// Initialize GLFW
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	// Set OpenGL version to 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Using CORE profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a window
	GLFWwindow* window = glfwCreateWindow(800, 800, "Window", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	// Load GLAD so it configures OpenGL
	if (!gladLoadGL()) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glViewport(0, 0, 800, 800);


	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shader("default.vert", "default.frag");


	// Generate Vertex Array Objects, Vertex Buffer Objects, and Element Buffer Objects
	VAO carVAO, frontSensorVAO, backSensorVAO;
	VBO carVBO(carVertices, sizeof(carVertices)), frontSensorVBO(frontSensorVertices, sizeof(frontSensorVertices)), backSensorVBO(backSensorVertices, sizeof(backSensorVertices));
	EBO carEBO(indices, sizeof(indices)), frontSensorEBO(indices, sizeof(indices)), backSensorEBO(indices, sizeof(indices));

	setupVAO(carVAO, carVBO, carEBO, carVertices, sizeof(carVertices), indices, sizeof(indices));
	setupVAO(frontSensorVAO, frontSensorVBO, frontSensorEBO, frontSensorVertices, sizeof(frontSensorVertices), indices, sizeof(indices));
	setupVAO(backSensorVAO, backSensorVBO, backSensorEBO, backSensorVertices, sizeof(backSensorVertices), indices, sizeof(indices));


	Texture carTexture("Textures/car_model.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	carTexture.texUnit(shader, "tex0", 0);

	Texture frontCarSensor[4] = {
		Texture("Textures/front_off.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("Textures/front_outermost.png", GL_TEXTURE_2D, GL_TEXTURE2, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("Textures/front_middle.png", GL_TEXTURE_2D, GL_TEXTURE3, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("Textures/front_nearest.png", GL_TEXTURE_2D, GL_TEXTURE4, GL_RGB, GL_UNSIGNED_BYTE)
	};

	Texture backCarSensor[4] = {
		Texture("Textures/rear_off.png", GL_TEXTURE_2D, GL_TEXTURE5, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("Textures/rear_outermost.png", GL_TEXTURE_2D, GL_TEXTURE6, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("Textures/rear_middle.png", GL_TEXTURE_2D, GL_TEXTURE7, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("Textures/rear_nearest.png", GL_TEXTURE_2D, GL_TEXTURE8, GL_RGB, GL_UNSIGNED_BYTE)
	};

	for (int i = 0; i < 4; ++i) {
		frontCarSensor[i].texUnit(shader, ("frontTex" + std::to_string(i)).c_str(), 1 + i);
		backCarSensor[i].texUnit(shader, ("backTex" + std::to_string(i)).c_str(), 5 + i);
	};

	// Gets ID of uniform called "scale"
	GLuint uniID = glGetUniformLocation(shader.ID, "scale");

	while (!glfwWindowShouldClose(window))
	{
		// Background color - black
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);

		// Tell OpenGL which Shader Program we want to use
		shader.Activate();

		// Assigns a value to the scaler;
		glUniform1f(uniID, 0.25f);
		
		RenderCar(carVAO, carTexture);

		RenderFrontSensors(shader, frontSensorVAO, frontCarSensor, 0);
		RenderBackSensors(shader, backSensorVAO, backCarSensor, 0);

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we have created and terminate the program
	carVAO.Delete();
	carVBO.Delete();
	carEBO.Delete();

	frontSensorVAO.Delete();
	frontSensorVBO.Delete();
	frontSensorEBO.Delete();

	backSensorVAO.Delete();
	backSensorVBO.Delete();
	backSensorEBO.Delete();

	carTexture.Delete();
	for (auto& tex : frontCarSensor) tex.Delete();
	for (auto& tex : backCarSensor) tex.Delete();
	shader.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}