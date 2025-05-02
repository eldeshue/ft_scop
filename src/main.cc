
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

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
#include "WavefrontObjectParser.h"

extern "C"
{
#include "ft_math/ft_math.h"
}

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
	glEnable(GL_DEPTH_TEST);

	/*------------------------- Parse --------------------------------*/
	// file open
	std::fstream objFileStream(objFilePathName.data());
	if (!objFileStream.is_open())
	{
		std::cerr << "Error : failed to open the file" << std::endl;
		return -1;
	}

	// read file
	std::stringstream objSStream;
	objSStream << objFileStream.rdbuf();

	// parse, get wavefront 3D object
	std::deque<WfObj*> renderObjBuf = WfParser::parse(objFilePathName, objSStream);	// for further purpose, we need scene file

	/*-------------------------- Get Render Resources --------------------------------*/

	GLuint const hTexture = CreateTexture2D("./textures/container.jpg");

	Shader texturedShaderProgram("./shader/VertexShader.glsl", "./shader/TexturedFShader.glsl");
	Shader checkeredShaderProgram("./shader/VertexShader.glsl", "./shader/NonTexturedFShader.glsl");
	if (texturedShaderProgram.ID == 0 || checkeredShaderProgram.ID == 0)
	{
		std::cerr << "Error : Shader creation failed" << std::endl;
		glfwTerminate();
		return -1;
	}

	/* ------------------------------- Define Scene -----------------------------------*/

	std::vector<WfObjView> renderTargets;
	std::transform(renderObjBuf.begin(), renderObjBuf.end(), std::back_inserter(renderTargets),
		[&](WfObj* obj) {
			auto& buffer = obj->getVtxBuffer();
			for (size_t i = 0; i < buffer.size(); ++i)
			{
				// check coloring
				int const q = (i / 3) % 4;
				switch (q)
				{
				case 0:
					buffer[i].vnx = 0.1f;
					buffer[i].vny = 0.1f;
					buffer[i].vnz = 0.1f;
					break;
				case 1:
					buffer[i].vnx = 0.2f;
					buffer[i].vny = 0.2f;
					buffer[i].vnz = 0.2f;
					break;
				case 2:
					buffer[i].vnx = 0.3f;
					buffer[i].vny = 0.3f;
					buffer[i].vnz = 0.3f;
					break;
				case 3:
					buffer[i].vnx = 0.4f;
					buffer[i].vny = 0.4f;
					buffer[i].vnz = 0.4f;
					break;
				default:
					// unreachable
					break;
				}

				// texture coordinate setting
				buffer[i].tx = buffer[i].py;
				buffer[i].ty = buffer[i].pz;

			}
			obj->initHandles();
			return WfObjView(ftmf4_set_vector(0.0, 0.0, 0.0, 1.0), 0, 0, 10.0, obj, checkeredShaderProgram.ID, hTexture);
		});

	FtCamera camera(ftmf4_set_vector(0, 0, -60.0, 1), 5.0f, 1000.0f, static_cast<float>(VIEWPORT_WIDTH) / VIEWPORT_HEIGHT, 45.0f);

	std::tuple<WfObjView*, FtCamera*, GLuint, GLuint> renderContext = std::make_tuple(
		&renderTargets.front(),
		&camera,
		texturedShaderProgram.ID,
		checkeredShaderProgram.ID
	);

	// set context to the window's event loop
	glfwSetWindowUserPointer(hWindow, &renderContext);

	// set events handled by glfw window
	RegisterInputEvent(hWindow);

	// render loop, each iteration consist a frame
	while (!glfwWindowShouldClose(hWindow))
	{
		HandleInput(hWindow);

		// render routine start
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// draw call
		std::for_each(renderTargets.begin(), renderTargets.end(),
			[&](WfObjView& objv) {
				objv.moveAngle(0.05, 0.0);
				objv.draw(camera.getVPMatrix());
			});

		glfwSwapBuffers(hWindow);
		glfwPollEvents();	// check event
	}

	// clean up resources
	glDeleteTextures(1, &hTexture);
	std::for_each(renderObjBuf.begin(), renderObjBuf.end(), [](WfObj* obj) { obj->deleteHandles(); delete obj; });
	glfwTerminate();	// window and OpenGL context destruction

	return 0;
}
