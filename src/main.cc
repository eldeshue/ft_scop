
#include <iostream>

extern "C" {
#include <glad/glad.h>
#include <GLFW/glfw3.h>
}

int main()
{
	/*------------------------- GLFW ---------------------------------*/
	// glfw init
	glfwInit();

	// glfWindowHint
	// first arg : type of option
	// secondactual value of option
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);	// major version of OpenGL, 3,0
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);	// minor version of OpenGL, 0.3

	// OpenGL mode, core-profile mode
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// for mac os
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

}
