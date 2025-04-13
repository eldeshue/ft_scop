
#ifndef GLFW_WINDOWS_H
#define GLFW_WINDOWS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

constexpr const int WINDOW_WIDTH = 800;
constexpr const int WINDOW_HEIGHT = 600;

constexpr const int VIEWPORT_LD_X = 0;
constexpr const int VIEWPORT_LD_Y = 0;

constexpr const int VIEWPORT_WIDTH = 800;
constexpr const int VIEWPORT_HEIGHT = 600;

void SetGLFWOption();
void RegisterInputEvent(GLFWwindow* const hWindow);
void HandleInput(GLFWwindow* const hWindow);

#endif
