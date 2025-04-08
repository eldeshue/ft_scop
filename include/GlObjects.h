
#ifndef GL_OBJECTS_H
#define GL_OBJECTS_H

#include <glad/glad.h>
#include <vector>

// image loading
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

typedef struct Point {
	float x, y, z;
	float r, g, b;
	float tx, ty;
} Point;

GLuint CreateBO();
GLuint CreateVBO(std::vector<Point> const& vertices);
GLuint CreateEBO(std::vector<uint32_t> const& indices);
GLuint CreateVAO(GLuint const hVBO, GLuint const hEBO);

GLuint CreateTexture2D(char const* const imagePathName);

#endif
