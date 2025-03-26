
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
		{-0.5f, -0.5f, 0.0f},
		{0.5f, -0.5f, 0.0f},
		{0.0f, 0.5f, 0.0f},
		{0.3f, -0.8f, 0.0f},
		{1.0f, 0.1f, 0.0f}
	};

	std::vector<uint32_t> indices1 = {
		0, 2, 1,
		0, 1, 3,
	};
	std::vector<uint32_t> indices2 = {
		2, 1, 4,
		1, 3, 4
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
		"out vec4 FragColor;\n"
		"void main()\n"
		"{ FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);}\0";	// decide color of fragment, orange
	char const* const fragmentShaderSource2 =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{ FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);}\0";	// decide color of fragment, orange

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

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// render routine start
		RenderTriangles(2, hVAO1, hShaderProgram1);
		RenderTriangles(2, hVAO2, hShaderProgram2);

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

