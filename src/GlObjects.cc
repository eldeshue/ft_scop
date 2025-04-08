
// image loading
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "GlObjects.h"

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

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Point), reinterpret_cast<void*>(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Point), reinterpret_cast<void*>(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
	// end setting

	return hVAO;
}

GLuint CreateTexture2D(char const* const imagePathName)
{
	// create texture
	GLuint hTexture = 0;
	glGenTextures(1, &hTexture);

	// bind texture as 2d texture
	glBindTexture(GL_TEXTURE_2D, hTexture);

	// setting options, need binding
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// wrap options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	// wrap options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);	// minification, mipmap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// magnification, filter

	// load image
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);	// flip image to match the coordinate between texture and NDC
	u_char* data = stbi_load(imagePathName, &width, &height, &nrChannels, 0);
	if (data)
	{
		// init texture with image
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		return 0;
	}
	stbi_image_free(data);
	return hTexture;
}
