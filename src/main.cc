
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

extern "C"
{
#include "ft_math/ft_math.h"
}

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

	/*-------------------------- Config GL and window --------------------------------*/
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

	/*------------------------- Parse --------------------------------*/

	// initialze filestream

	// parse and initialze resources

	// Get render resource
	// vertices, render topology, texture(?)
	std::vector<Point> vertices = {
		{-50, 50, 0, 1.0, 0.0, 0.0, 0.0, 1.0},
		{50, 50, 0, 0.0, 1.0, 0.0, 1.0, 1.0},
		{50, -50, 0, 0.0, 0.0, 1.0, 1.0, 0.0},
		{-50, -50, 0, 1.0, 1.0, 1.0, 0.0, 0.0}
	};

	std::vector<uint32_t> indices1 = {
		0, 3, 1,
		1, 3, 2
	};

	/*-------------------------- Get Render Resources --------------------------------*/
	glEnable(GL_DEPTH_TEST);

	GLuint const hVBO = CreateVBO(vertices);
	GLuint const hEBO = CreateEBO(indices1);
	GLuint const hVAO = CreateVAO(hVBO, hEBO);
	GLuint const hTexture = CreateTexture2D("./textures/container.jpg");

	Shader shaderProgram("./shader/VertexShader.glsl", "./shader/FragmentShader.glsl");
	if (shaderProgram.ID == 0)
	{
		std::cerr << "Error : Shader creation failed" << std::endl;
		glfwTerminate();
		return -1;
	}
	GLint mvpMatUniformLoc = glGetUniformLocation(shaderProgram.ID, "mvp");

	/* ------------------------------- Define Scene -----------------------------------*/

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// define model matrix(local to world matrix) for the object
	// update by arrow key(translate)
	// update by time(rotation z axis)
	t_FTMFLOAT4X4 modelMatrix = ftmf44_set_scale(ftmf4_set_vector(0.1, 0.1, 0.1, 1));

	// define camera, build view matrix
	// from camera, we can define view matrix
	// use wasd key to walk camera
	// use mouse to rotate camera
	// use mouse scroll key to zoom
	t_FTMFLOAT4 camPos = ftmf4_set_vector(0, 0, -10.0, 1);
	t_FTMFLOAT4 camTarget = ftmf4_set_vector(0, 0, 0, 1);
	t_FTMFLOAT4 camUp = ftmf4_set_vector(0, 1, 0, 1);
	t_FTMFLOAT4X4 viewMatrix = ftmf44_set_view(camPos, camTarget, camUp);

	// build perspective matrix
	// near plane, far plane, fov
	// get perspective matrix from view port
	// fov will be updated by screen resizing
	float distNearestPlane = 5.0f;
	float distFarestPlane = 15.0f;
	float verticalFovRad = M_PI / 2;
	float aspectRatio = static_cast<float>(VIEWPORT_WIDTH) / VIEWPORT_HEIGHT;

	// OpenGL Style, [-1, 1]
	t_FTMFLOAT4X4 perspectiveMatrix = ftmf44_set_scale(ftmf4_set_vector(
		1.0f / (tanf(verticalFovRad / 2) * aspectRatio),
		1.0f / tanf(verticalFovRad / 2),
		(distFarestPlane + distNearestPlane) / (distFarestPlane - distNearestPlane),
		1.0f));
	perspectiveMatrix.data[2][3] = 1.0f;
	perspectiveMatrix.data[3][3] = 0.0f;
	perspectiveMatrix.data[3][2] = -2 * (distFarestPlane * distNearestPlane) / (distFarestPlane - distNearestPlane);

	/*
	// DirectX Style, [0, 1]
	t_FTMFLOAT4X4 perspectiveMatrix = ftmf44_set_scale(ftmf4_set_vector(
		1.0f / (tanf(verticalFovRad / 2) * aspectRatio),
		1.0f / tanf(verticalFovRad / 2),
		(distFarestPlane) / (distFarestPlane - distNearestPlane),
		1.0f));
	perspectiveMatrix.data[2][3] = 1.0f;
	perspectiveMatrix.data[3][3] = 0.0f;
	perspectiveMatrix.data[3][2] = -(distFarestPlane * distNearestPlane) / (distFarestPlane - distNearestPlane);
	*/

	t_FTMFLOAT4X4 mv = ftmf44_mult(&modelMatrix, &viewMatrix);
	t_FTMFLOAT4X4 mvp = ftmf44_mult(&mv, &perspectiveMatrix);

	for (int r = 0; r < 4; ++r)
	{
		for (int c = 0; c < 4; ++c)
		{
			std::cout << mvp.data[r][c] << ' ';
		}
		std::cout << '\n';
	}
	// init descriptor for glfw event

	// load matrix as uniform to the shader

	// render loop, each iteration consist a frame
	while (!glfwWindowShouldClose(hWindow))
	{
		HandleInput(hWindow);


		// render routine start
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// update resource
		shaderProgram.use();
		glUniformMatrix4fv(mvpMatUniformLoc, 1, GL_FALSE, mvp.data[0]);

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

