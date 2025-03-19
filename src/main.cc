
#include <iostream>
#include <functional>
#include <string_view>

extern "C" {
#include <glad/glad.h>
#include <GLFW/glfw3.h>
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
	std::string_view obj_file_path_name(argv[1]);
	if (obj_file_path_name.size() <= 4 ||
		obj_file_path_name.substr(obj_file_path_name.size() - 4) != ".obj")
	{
		std::cerr << "Error : input file must end with \'.obj\'" << std::endl;
		return -1;
	}

	/*------------------------- Parse --------------------------------*/

	// initialze filestream

	// parse and initialze resources

	// vertices, render topology, texture(?)

	/*-------------------------- GLFW --------------------------------*/
	// glfw init
	glfwInit();

	// glfWindowHint
	// first arg : type of option
	// secondactual value of option
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);	// major version of OpenGL, 3,0
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);	// minor version of OpenGL, 0.3

	// OpenGL mode, core-profile mode
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// for mac os only
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// create window object
	GLFWwindow* hWindow = glfwCreateWindow(800, 600, "ft_scop", NULL, NULL);
	if (hWindow == NULL)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(hWindow);

	/*----------------------------------- GLAD --------------------------------------*/

	// run GLAD to load OpenGL
	// if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		std::cerr << "Error : Failed to initialize GLAD" << std::endl;
		return -1;
	}
	// define view port
	glViewport(0, 0, 800, 600);

	/*----------------------------------- Event --------------------------------------*/

	// resizing event
	glfwSetFramebufferSizeCallback(hWindow, [](GLFWwindow* phWin, int w, int h) {
		uintptr_t test = reinterpret_cast<uintptr_t>(phWin);
		std::cerr << "debug: resize " << test << std::endl;
		glViewport(0, 0, w, h);
		});	// register call-back, capture-less lambda implicitly converts to function pointer


	/*----------------------------------- Render --------------------------------------*/

	while (!glfwWindowShouldClose(hWindow))
	{
		glfwSwapBuffers(hWindow);
		glfwPollEvents();	// wait event
	}

	/*----------------------------------- Render --------------------------------------*/

	// clean up resources
	glfwTerminate();

	return 0;
}
