
#include "GlfwWindows.h"
#include "FtCamera.h"
#include "WavefrontObjectView.h"
#include "Shader.h"

using UpdateContext = std::tuple<WfObjView*, FtCamera*, GLuint, GLuint>;

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
		auto [pObjv, pCam, hTextureShader, hCheckerShader] = *static_cast<UpdateContext*>(glfwGetWindowUserPointer(phWin));

		pCam->setAspectRatio(static_cast<float>(w) / h);
		glViewport(VIEWPORT_LD_X, VIEWPORT_LD_Y, w, h);
		});	// register call-back, capture-less lambda implicitly converts to function pointer

	// mouse cursor move
	glfwSetCursorPosCallback(hWindow, [](GLFWwindow* phWin, double curX, double curY) {
		static double prevX = curX;
		static double  prevY = curY;
		static double const sRot = 0.4;

		// update
		auto [pObjv, pCam, hTextureShader, hCheckerShader] = *static_cast<UpdateContext*>(glfwGetWindowUserPointer(phWin));
		if (pCam->getRot())
		{
			pCam->moveAngle(-(curX - prevX) * sRot, -(curY - prevY) * sRot);
		}
		prevX = curX;
		prevY = curY;
		});

	// mouse cursor drag
	glfwSetMouseButtonCallback(hWindow, [](GLFWwindow* phWin, int button, int action, int mods) {
		auto [pObjv, pCam, hTextureShader, hCheckerShader] = *static_cast<UpdateContext*>(glfwGetWindowUserPointer(phWin));
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
		auto [pObjv, pCam, hTextureShader, hCheckerShader] = *static_cast<UpdateContext*>(glfwGetWindowUserPointer(phWin));
		static double const sensitivity = 2.5;
		pCam->zoom(-sensitivity * (xOffset + yOffset));
		});

	// key input
	glfwSetKeyCallback(hWindow, [](GLFWwindow* phWin, int key, int scanCode, int action, int mode) {
		static constexpr float const vel = 1.2;
		static bool isWireFrame = false;

		auto [pObjv, pCam, hTextureShader, hCheckerShader] = *static_cast<UpdateContext*>(glfwGetWindowUserPointer(phWin));
		scanCode = 0;
		mode = 0;
		isWireFrame += mode + scanCode;
		if (action == GLFW_PRESS)
		{
			switch (key) {
			case GLFW_KEY_TAB:	// toggle wireframe rendering
				if (isWireFrame == false)
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
					isWireFrame = true;
				}
				else
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
					isWireFrame = false;
				}
				break;
			case GLFW_KEY_BACKSPACE:
				pCam->resetPose();
				break;
			case GLFW_KEY_LEFT_CONTROL:	// toggle shader
				if (pObjv->getShader() == hTextureShader)
					pObjv->setShader(hCheckerShader);
				else
					pObjv->setShader(hTextureShader);
				break;
			}
		}
		switch (key) {
		case GLFW_KEY_W:	// move camera
			pCam->movePos(0.0f, 0.0f, vel);
			break;
		case GLFW_KEY_A:
			pCam->movePos(-vel, 0.0f, 0.0f);
			break;
		case GLFW_KEY_S:
			pCam->movePos(0.0f, 0.0f, -vel);
			break;
		case GLFW_KEY_D:
			pCam->movePos(vel, 0.0f, 0.0f);
			break;
		case GLFW_KEY_Z:
			pCam->movePos(0.0f, -vel, 0.0f);
			break;
		case GLFW_KEY_X:
			pCam->movePos(0.0f, vel, 0.0f);
			break;
		case GLFW_KEY_UP:	// move objeect
			pObjv->movePos(0.0f, 0.0f, vel);
			break;
		case GLFW_KEY_LEFT:
			pObjv->movePos(-vel, 0.0f, 0.0f);
			break;
		case GLFW_KEY_DOWN:
			pObjv->movePos(0.0f, 0.0f, -vel);
			break;
		case GLFW_KEY_RIGHT:
			pObjv->movePos(vel, 0.0f, 0.0f);
			break;
		case GLFW_KEY_COMMA:
			pObjv->movePos(0.0f, -vel, 0.0f);
			break;
		case GLFW_KEY_PERIOD:
			pObjv->movePos(0.0f, vel, 0.0f);
			break;
		}
		});
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
