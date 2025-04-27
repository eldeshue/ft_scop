
#include <iostream>
#include <string_view>
#include <vector>
#include <cmath>

// set OpenGL
#include <glad/glad.h>
#include "GlfwWindows.h"

// render resources
#include "GlObjects.h"
#include "Shader.h"

#include "FtCamera.h"
#include "WavefrontObject.h"
#include "WavefrontObjectView.h"

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

	/*------------------------- Parse --------------------------------*/

	// initialze filestream

	// parse and initialze resources

	// Get render resource
	// vertices, render topology, texture(?)
	WfObj obj("test obj");
	obj.getVPosBuffer() = { {-50, 50, 0}, {50, 50, 0}, {50, -50, 0}, {-50, -50, 0} };
	obj.getNVecBuffer() = { {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 1.0, 1.0} };
	obj.getTexPosBuffer() = { {0.0, 1.0}, {1.0, 1.0}, {1.0, 0.0}, {0.0, 0.0} };
	obj.getIdxBuffer() = {
		0, 3, 1,
		1, 3, 2
	};

	/*-------------------------- Get Render Resources --------------------------------*/
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

	t_FTMFLOAT4X4 modelMatrix = ftmf44_set_scale(ftmf4_set_vector(0.1, 0.1, 0.1, 1));

	WfObjView objv(ftmf4_set_vector(0.0, 0.0, 0.0, 1.0), 0, 0, 0.1, &obj, shaderProgram.ID, hTexture);

	FtCamera camera(ftmf4_set_vector(0, 0, -10.0, 1), 1.0f, 100.0f, static_cast<float>(VIEWPORT_WIDTH) / VIEWPORT_HEIGHT, 45.0f);
	glfwSetWindowUserPointer(hWindow, &camera);

	// set events handled by glfw window
	RegisterInputEvent(hWindow);

	// render loop, each iteration consist a frame
	while (!glfwWindowShouldClose(hWindow))
	{
		HandleInput(hWindow);

		// render routine start
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// draw call
		t_FTMFLOAT4X4 vp = camera.getVPMatrix();
		objv.draw(vp);

		glfwSwapBuffers(hWindow);
		glfwPollEvents();	// check event
	}

	// clean up resources
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

