
#include <iostream>
#include <functional>
#include <string_view>
#include <vector>
#include <array>
#include <tuple>

extern "C" {
#include <glad/glad.h>
#include <GLFW/glfw3.h>
}

constexpr const int WINDOW_WIDTH = 800;
constexpr const int WINDOW_HEIGHT = 600;

constexpr const int VIEWPORT_LD_X = 0;
constexpr const int VIEWPORT_LD_Y = 0;

constexpr const int VIEWPORT_WIDTH = 800;
constexpr const int VIEWPORT_HEIGHT = 600;

void SetGLFWOption();
void RegisterInputEvent(GLFWwindow* const hWindow);
void HandleInput(GLFWwindow* const hWindow);

GLuint CreateVertexShader(char const* const shaderSource);
GLuint CreateFragmentShader(char const* const shaderSource);

void RenderObject();

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
	using Point = std::tuple<float, float, float>;
	std::array<Point, 3> vertices = { {
		{-0.5f, -0.5f, 0.0f},
		{0.5f, -0.5f, 0.0f},
		{0.0f, 0.5f, 0.0f}
	} };

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
		return -1;
	}

	// define view port
	glViewport(VIEWPORT_LD_X, VIEWPORT_LD_Y, VIEWPORT_WIDTH, VIEWPORT_HEIGHT);

	RegisterInputEvent(hWindow);

	// render resource loading

	// vertex buffer
	GLuint hVBO;
	glGenBuffers(1, &hVBO);	// create buffer and get it's handle
	glBindBuffer(GL_ARRAY_BUFFER, hVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);	// no change, multiple rendering

	// shader compile and loading
	char const* const vertexShaderSource =
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	char const* const fragmentShaderSource =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{ FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);}\0";	// decide color of fragment orange

	GLuint hVShader = CreateVertexShader(vertexShaderSource);
	GLuint hFShader = CreateFragmentShader(fragmentShaderSource);
	if (hVShader == -1 || hFShader == -1)
	{
		// shader compile failed
		exit(1);
	}


	// render loop, each iteration consist a frame
	while (!glfwWindowShouldClose(hWindow))
	{
		HandleInput(hWindow);

		// render routine start
		RenderObject();

		glfwSwapBuffers(hWindow);
		glfwPollEvents();	// check event
	}

	// clean up resources
	glDeleteBuffers(1, &hVBO);	// vertex buffer delete

	glfwTerminate();	// window destroy

	return 0;
}

/**
 * @brief set state of glfw
 */
void SetGLFWOption()
{
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
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

/**
 * @brief register input event to handle
 */
void RegisterInputEvent(GLFWwindow* const hWindow)
{
	// resizing
	glfwSetFramebufferSizeCallback(hWindow, [](GLFWwindow* phWin, int w, int h) {
		uintptr_t test = reinterpret_cast<uintptr_t>(phWin);
		std::cerr << "debug: resize " << test << std::endl;
		glViewport(VIEWPORT_LD_X, VIEWPORT_LD_Y, w, h);
		});	// register call-back, capture-less lambda implicitly converts to function pointer

}

/**
 * @brief Handling input, keys
 */
void HandleInput(GLFWwindow* const hWindow)
{
	// esc key input
	if (glfwGetKey(hWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(hWindow, true);
}

/**
 * @brief get GLSL source string and create vertex shader
 */
GLuint CreateVertexShader(char const* const shaderSource)
{
	GLuint hVertexShader = glCreateShader(GL_VERTEX_SHADER);// create vertex shader handle
	glShaderSource(hVertexShader, 1, &shaderSource, NULL);	// set multiple shader source file
	glCompileShader(hVertexShader);							// compile and link

	int isVertexShaderCompileSuccess = 0;
	char infoLog[512];
	glGetShaderiv(hVertexShader, GL_COMPILE_STATUS, &isVertexShaderCompileSuccess);
	if (!isVertexShaderCompileSuccess)
	{
		glGetShaderInfoLog(hVertexShader, 512, NULL, infoLog);
		std::cerr << "Error : vertex shader compilation failed\n" << infoLog << std::endl;
		return -1;
	}
	return hVertexShader;
}

/**
 * @brief get GLSL source string and create fragment shader
 */
GLuint CreateFragmentShader(char const* const shaderSource)
{
	GLuint hFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(hFragmentShader, 1, &shaderSource, NULL);
	glCompileShader(hFragmentShader);

	int isFragmentShaderCompileSuccess = 0;
	char infoLog[512];
	glGetShaderiv(hFragmentShader, GL_COMPILE_STATUS, &isFragmentShaderCompileSuccess);
	if (!isFragmentShaderCompileSuccess)
	{
		glGetShaderInfoLog(hFragmentShader, 512, NULL, infoLog);
		std::cerr << "Error : fragment shader compilation failed\n" << infoLog << std::endl;
		return -1;
	}
	return hFragmentShader;
}

/**
 * @brief render object
 */
void RenderObject()
{

}

