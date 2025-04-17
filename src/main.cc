
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

#include "FtCamera.h"

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


	t_FTMFLOAT4X4 modelMatrix = ftmf44_set_scale(ftmf4_set_vector(0.1, 0.1, 0.1, 1));
	FtCamera camera(ftmf4_set_vector(0, 0, -10.0, 1), 1.0f, 100.0f, static_cast<float>(VIEWPORT_WIDTH) / VIEWPORT_HEIGHT, 45.0f);

	glfwSetWindowUserPointer(hWindow, &camera);
	RegisterInputEvent(hWindow);

	camera.setAngle(0.0f, -89.0f);
	t_FTMFLOAT4X4 test = camera.getVMatrix();
	for (int r = 0; r < 4; ++r)
	{
		for (int c = 0; c < 4; ++c)
		{
			std::cout << test.data[r][c] << ' ';
		}
		std::cout << '\n';
	}
	// t_FTMFLOAT4 test = ftmf4_set_vector(50.0f, 50.0f, 0.0f, 1.0f);
	// for (int pitch = -89; pitch <= 0; ++pitch)
	// {
	// 	camera.setAngle(0.0f, pitch);
	// 	t_FTMFLOAT4X4 vp = camera.getVPMatrix();
	// 	t_FTMFLOAT4X4 mvp = ftmf44_mult(&modelMatrix, &vp);
	// 	t_FTMFLOAT4 result = ftmf44_affine(&test, &mvp);
	// 	std::cout << "Pitch : " << pitch << " RU pos : " << result.data[0] << ' ' << result.data[1] << ' ' << result.data[2] << ' ' << result.data[3] << '\n';
	// 	if ([](t_FTMFLOAT4 const& p) {
	// 		for (int i = 0; i < 3; ++i)
	// 		{
	// 			const float f = p.data[i] / p.data[3];
	// 			if (f < -1.0f || 1.0f < f)
	// 			{
	// 				return false;
	// 			}
	// 		}
	// 		return true;
	// 		}(result))
	// 	{
	// 		std::cout << "In NDC\n";
	// 	}
	// 	else
	// 	{
	// 		std::cout << "Out NDC\n";
	// 	}
	// }

	// render loop, each iteration consist a frame
	while (!glfwWindowShouldClose(hWindow))
	{
		HandleInput(hWindow);

		t_FTMFLOAT4X4 vp = camera.getVPMatrix();
		t_FTMFLOAT4X4 mvp = ftmf44_mult(&modelMatrix, &vp);

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

