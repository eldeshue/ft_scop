
#include "GlfwWindows.h"
#include "FtCamera.h"

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
		FtCamera* const pCam = static_cast<FtCamera*>(glfwGetWindowUserPointer(phWin));

		pCam->setAspectRatio(static_cast<float>(w) / h);
		glViewport(VIEWPORT_LD_X, VIEWPORT_LD_Y, w, h);
		});	// register call-back, capture-less lambda implicitly converts to function pointer

	// mouse cursor move
	glfwSetCursorPosCallback(hWindow, [](GLFWwindow* phWin, double curX, double curY) {
		static double prevX = curX;
		static double  prevY = curY;
		static double const sRot = 0.4;

		// update
		FtCamera* const pCam = static_cast<FtCamera*>(glfwGetWindowUserPointer(phWin));
		if (pCam->getRot())
		{
			pCam->moveAngle((curX - prevX) * sRot, -(curY - prevY) * sRot);
		}
		prevX = curX;
		prevY = curY;
		});

	// mouse cursor drag
	glfwSetMouseButtonCallback(hWindow, [](GLFWwindow* phWin, int button, int action, int mods) {
		FtCamera* const pCam = static_cast<FtCamera*>(glfwGetWindowUserPointer(phWin));
		if (button == GLFW_MOUSE_BUTTON_LEFT)
		{
			mods = 0;
			if (action == GLFW_PRESS)
				pCam->setRot(true);
			else if (action == GLFW_RELEASE)
				pCam->setRot(false + mods);
		}
		});

	// mouse scroll
	glfwSetScrollCallback(hWindow, [](GLFWwindow* phWin, double xOffset, double yOffset) {
		FtCamera* const pCam = static_cast<FtCamera*>(glfwGetWindowUserPointer(phWin));
		static double const sensitivity = 2.5;
		pCam->zoom(-sensitivity * (xOffset + yOffset));
		});

	// key input
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
