
#include <iostream>
#include <functional>
#include <string_view>
#include <vector>
#include <array>
#include <tuple>
#include <cmath>

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

typedef struct Point {
	float x;
	float y;
	float z;
} Point;

GLuint CreateBO();
GLuint CreateVBO(std::vector<Point> const& vertices);
GLuint CreateEBO(std::vector<uint32_t> const& indices);
GLuint CreateVAO(GLuint const hVBO, GLuint const hEBO);

GLuint CreateVertexShader(char const* const shaderSource);
GLuint CreateFragmentShader(char const* const shaderSource);
GLuint CreateShaderProgram(GLuint const hVShader, GLuint const hFShader);

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
		{-0.5f, -0.6f, 0.0f},
		{0.5f, -0.6f, 0.0f},
		{-0.0f, 0.6f, 0.0f},
		{0.3f, -0.9f, 0.0f},
		{-0.5f, 0.9f, 0.0f},
		{0.3f, -0.3f, 0.0f},
		{-0.8f, -0.1f, 0.0f},
		{0.5f, -0.9f, 0.0f},
		{0.3f, -0.1f, 0.0f},
		{1.0f, 0.1311f, 0.0f}
	};

	std::vector<uint32_t> indices1 = {
	0, 1, 2,
	0, 1, 3,
	0, 1, 4,
	0, 1, 5,
	0, 1, 6,
	0, 1, 7,
	0, 1, 8,
	0, 1, 9,
	0, 2, 3,
	0, 2, 4,
	0, 2, 5,
	0, 2, 6,
	0, 2, 7,
	0, 2, 8,
	0, 2, 9,
	0, 3, 4,
	0, 3, 5,
	0, 3, 6,
	0, 3, 7,
	0, 3, 8,
	0, 3, 9,
	0, 4, 5,
	0, 4, 6,
	0, 4, 7,
	0, 4, 8,
	0, 4, 9,
	0, 5, 6,
	0, 5, 7,
	0, 5, 8,
	0, 5, 9,
	0, 6, 7,
	0, 6, 8,
	0, 6, 9,
	0, 7, 8,
	0, 7, 9,
	0, 8, 9,
	1, 2, 3,
	1, 2, 4,
	1, 2, 5,
	1, 2, 6,
	1, 2, 7,
	1, 2, 8,
	1, 2, 9,
	1, 3, 4,
	1, 3, 5,
	1, 3, 6,
	1, 3, 7,
	1, 3, 8,
	1, 3, 9,
	1, 4, 5,
	1, 4, 6,
	1, 4, 7,
	1, 4, 8,
	1, 4, 9,
	1, 5, 6,
	1, 5, 7,
	1, 5, 8,
	1, 5, 9,
	1, 6, 7,
	};
	std::vector<uint32_t> indices2 = {
	1, 6, 8,
	1, 6, 9,
	1, 7, 8,
	1, 7, 9,
	1, 8, 9,
	2, 3, 4,
	2, 3, 5,
	2, 3, 6,
	2, 3, 7,
	2, 3, 8,
	2, 3, 9,
	2, 4, 5,
	2, 4, 6,
	2, 4, 7,
	2, 4, 8,
	2, 4, 9,
	2, 5, 6,
	2, 5, 7,
	2, 5, 8,
	2, 5, 9,
	2, 6, 7,
	2, 6, 8,
	2, 6, 9,
	2, 7, 8,
	2, 7, 9,
	2, 8, 9,
	3, 4, 5,
	3, 4, 6,
	3, 4, 7,
	3, 4, 8,
	3, 4, 9,
	3, 5, 6,
	3, 5, 7,
	3, 5, 8,
	3, 5, 9,
	3, 6, 7,
	3, 6, 8,
	3, 6, 9,
	3, 7, 8,
	3, 7, 9,
	3, 8, 9,
	4, 5, 6,
	4, 5, 7,
	4, 5, 8,
	4, 5, 9,
	4, 6, 7,
	4, 6, 8,
	4, 6, 9,
	4, 7, 8,
	4, 7, 9,
	4, 8, 9,
	5, 6, 7,
	5, 6, 8,
	5, 6, 9,
	5, 7, 8,
	5, 7, 9,
	5, 8, 9,
	6, 7, 8,
	6, 7, 9,
	6, 8, 9,
	7, 8, 9
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
		return -1;
	}

	// define view port
	glViewport(VIEWPORT_LD_X, VIEWPORT_LD_Y, VIEWPORT_WIDTH, VIEWPORT_HEIGHT);

	RegisterInputEvent(hWindow);

	// render resource loading

		// shader compile and loading
	char const* const vertexShaderSource =
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	char const* const fragmentShaderSource1 =
		"#version 330 core\n"
		"uniform float sinGreen;"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{ FragColor = vec4(0.0f, sinGreen, 0.0f, 1.0f);}\0";	// decide color of fragment, green
	char const* const fragmentShaderSource2 =
		"#version 330 core\n"
		"uniform float cosRed;"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{ FragColor = vec4(cosRed, 0.0f, 0.0f, 1.0f);}\0";	// decide color of fragment, orange

	GLuint hVShader = CreateVertexShader(vertexShaderSource);
	GLuint hFShader1 = CreateFragmentShader(fragmentShaderSource1);
	GLuint hFShader2 = CreateFragmentShader(fragmentShaderSource2);
	if (hVShader == 0 || hFShader1 == 0 || hFShader2 == 0)
	{
		// shader compile failed
		exit(1);
	}

	GLuint hShaderProgram1 = CreateShaderProgram(hVShader, hFShader1);
	GLuint hShaderProgram2 = CreateShaderProgram(hVShader, hFShader2);
	if (hShaderProgram1 == 0 || hShaderProgram2 == 0) return 1;

	glDeleteShader(hVShader);
	glDeleteShader(hFShader1);	// after link, no need shader object(reuse otherwise)
	glDeleteShader(hFShader2);

	// init render resources
	GLuint const hVBO = CreateVBO(vertices);
	GLuint const hEBO1 = CreateEBO(indices1);
	GLuint const hEBO2 = CreateEBO(indices2);
	GLuint const hVAO1 = CreateVAO(hVBO, hEBO1);
	GLuint const hVAO2 = CreateVAO(hVBO, hEBO2);

	/* ------------------------------- Define Scene -----------------------------------*/

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop, each iteration consist a frame
	while (!glfwWindowShouldClose(hWindow))
	{
		HandleInput(hWindow);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// update the uniform
		float t = glfwGetTime();
		float greenValue = sin(t) / 2.0f + 0.5f;
		float redValue = cos(t) / 2.0f + 0.5f;
		GLint hUniformSinGreen = glGetUniformLocation(hShaderProgram1, "sinGreen");
		GLint hUniformCosRed = glGetUniformLocation(hShaderProgram2, "cosRed");

		// update uniform

		// render routine start
		glUniform1f(hUniformSinGreen, greenValue);
		RenderTriangles(60, hVAO1, hShaderProgram1);

		glUniform1f(hUniformCosRed, redValue);
		RenderTriangles(60, hVAO2, hShaderProgram2);

		glfwSwapBuffers(hWindow);
		glfwPollEvents();	// check event
	}

	// clean up resources
	glDeleteVertexArrays(1, &hVAO1);
	glDeleteVertexArrays(1, &hVAO2);
	glDeleteBuffers(1, &hVBO);	// buffer delete
	glDeleteBuffers(1, &hEBO1);	// buffer delete
	glDeleteBuffers(1, &hEBO2);	// buffer delete
	glDeleteProgram(hShaderProgram1);
	glDeleteProgram(hShaderProgram2);

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
		std::cout << "Event : resize window " << w << ' ' << h << ' ' << test << '\n';
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

GLuint CreateBO()
{
	GLuint hBO = 0;
	glGenBuffers(1, &hBO);
	return hBO;
}

GLuint CreateVBO(std::vector<Point> const& vertices)
{
	GLuint hVBO = CreateBO();

	glBindBuffer(GL_ARRAY_BUFFER, hVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Point) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
	return hVBO;
}

GLuint CreateEBO(std::vector<uint32_t> const& indices)
{
	GLuint hEBO = CreateBO();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, hEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * indices.size(), indices.data(), GL_STATIC_DRAW);
	return hEBO;
}

GLuint CreateVAO(GLuint const hVBO, GLuint const hEBO)
{
	GLuint hVAO = 0;

	glGenVertexArrays(1, &hVAO);

	// start setting
	glBindVertexArray(hVAO);

	// EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, hEBO);

	// VBO, input layout
	glBindBuffer(GL_ARRAY_BUFFER, hVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Point), reinterpret_cast<void*>(0));	// map vbo and shader program input at 0
	glEnableVertexAttribArray(0); // enable layout of location 0, if another location exist another call needed

	glBindVertexArray(0);
	// end setting

	return hVAO;
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
		return 0;
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
		return 0;
	}
	return hFragmentShader;
}

GLuint CreateShaderProgram(GLuint const hVShader, GLuint const hFShader)
{
	GLuint hShaderProgram = glCreateProgram();
	glAttachShader(hShaderProgram, hVShader);
	glAttachShader(hShaderProgram, hFShader);
	glLinkProgram(hShaderProgram);	// link shaders, create executable
	int isShaderLinkSuccess = 0;
	glGetProgramiv(hShaderProgram, GL_LINK_STATUS, &isShaderLinkSuccess);
	if (!isShaderLinkSuccess) {
		//		glGetProgramInfoLog(hShaderProgram, 512, NULL, infoLog);
		std::cerr << "Error : shader link failed." << std::endl;
		return 0;
	}
	return hShaderProgram;
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

