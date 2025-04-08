
#include <iostream>
#include <functional>
#include <string_view>
#include <vector>
#include <array>
#include <cmath>

// set OpenGL
#include <glad/glad.h>
#include "GlfwWindows.h"

// render resources
#include "GlObjects.h"
#include "Shader.h"

// math
#include "ft_math/ft_math.h"

void RenderTriangles(GLsizei const numTri, GLuint const hVAO, GLuint const hShaderProgram);

int main(int argc, char* argv[])
{
	/*------------------------- Input --------------------------------*/

	// argument number check
	if (argc != 2)
	{
		std::cerr << "Error : wrong number of argument" << std::endl;
		return -1;
	}

	// argument sanity check
	std::string_view objFilePathName(argv[1]);
	if (objFilePathName.size() <= 4 ||
		objFilePathName.substr(objFilePathName.size() - 4) != ".obj")
	{
		std::cerr << "Error : input file must end with \'.obj\'" << std::endl;
		return -1;
	}

	/*------------------------- Parse --------------------------------*/

	// initialze filestream

	// parse and initialze resources

	// Get render resource
	// vertices, render topology, texture(?)
	std::vector<Point> vertices = {
		{-0.5, 0.5, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0},	// LU
		{0.5, 0.5, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0},	// RU
		{0.5, -0.5, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0},	// RD
		{-0.5, -0.5, 0.0, 1.0, 1.0, 1.0, 0.0, 0.0}	// LD
	};

	std::vector<uint32_t> indices1 = {
		0, 3, 1,
		1, 3, 2
	};

	/*-------------------------- GLFW --------------------------------*/
	// set glfw option
	SetGLFWOption();

	// create window object
	GLFWwindow* hWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "ft_scop", NULL, NULL);
	if (hWindow == NULL)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(hWindow);

	// load OpenGL by using GLAD
	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		std::cerr << "Error : Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}

	// define view port
	glViewport(VIEWPORT_LD_X, VIEWPORT_LD_Y, VIEWPORT_WIDTH, VIEWPORT_HEIGHT);

	RegisterInputEvent(hWindow);

	// render resource loading

	// shader compile and loading
	Shader shaderProgram("./shader/VertexShader.glsl", "./shader/FragmentShader.glsl");

	// init render resources
	GLuint const hVBO = CreateVBO(vertices);
	GLuint const hEBO = CreateEBO(indices1);
	GLuint const hVAO = CreateVAO(hVBO, hEBO);
	GLuint const hTexture = CreateTexture2D("./textures/container.jpg");

	if (hTexture == 0)
	{
		std::cerr << "Error : texture loading failed" << std::endl;
		glfwTerminate();
		return -1;
	}

	/* ------------------------------- Define Scene -----------------------------------*/

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// render loop, each iteration consist a frame
	while (!glfwWindowShouldClose(hWindow))
	{
		HandleInput(hWindow);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// render routine start
		glBindTexture(GL_TEXTURE_2D, hTexture);	// by binding texture, don't need to update uniform
		RenderTriangles(2, hVAO, shaderProgram.ID);

		glfwSwapBuffers(hWindow);
		glfwPollEvents();	// check event
	}

	// clean up resources
	glDeleteVertexArrays(1, &hVAO);
	glDeleteBuffers(1, &hVBO);	// buffer delete
	glDeleteBuffers(1, &hEBO);	// buffer delete
	glDeleteTextures(1, &hTexture);

	glfwTerminate();	// window destroy

	return 0;
}

/**
 * @brief render multiple triangles
 */
void RenderTriangles(GLsizei const numTri, GLuint const hVAO, GLuint const hShaderProgram)
{
	glUseProgram(hShaderProgram);	// bind shader program
	glBindVertexArray(hVAO);		// bind VAO
	glDrawElements(GL_TRIANGLES, numTri * 3, GL_UNSIGNED_INT, 0);	// topology, size, type, start offset
	glBindVertexArray(0);		// bind VAO
}

