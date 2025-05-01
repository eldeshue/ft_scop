
#include "WavefrontObject.h"

#include <iostream>
#include <numeric>

WfObj::WfObj(std::string const& name) :
	name(name),
	vertexBuf(),
	indexBuf(),
	hVAO(0)
{
	std::fill(hBO.begin(), hBO.end(), 0);
}


WfObj::WfObj(std::string const& name, std::deque<Vertex> const& faceVertexBuffer) :
	name(name),
	vertexBuf(faceVertexBuffer.begin(), faceVertexBuffer.end()),
	indexBuf(vertexBuf.size(), 0),
	hVAO(0)
{
	std::iota(indexBuf.begin(), indexBuf.end(), 0);
}

WfObj::~WfObj()
{
	if (hVAO != 0)
	{
		glDeleteVertexArrays(1, &hVAO);
		glDeleteBuffers(2, hBO.data());
	}
}

std::vector<Vertex>& WfObj::getVtxBuffer()
{
	return vertexBuf;
}

std::vector<uint32_t>& WfObj::getIdxBuffer()
{
	return indexBuf;
}

size_t WfObj::getIdxBufferSize() const
{
	return indexBuf.size();
}

// init handles
void WfObj::initHandles()
{
	// erase prev handles
	deleteHandles();

	// create new handles
	// create buffer objects
	glGenBuffers(2, hBO.data());

	// Vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, hBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexBuf.size(), vertexBuf.data(), GL_STATIC_DRAW);

	// EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, hBO[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * indexBuf.size(), indexBuf.data(), GL_STATIC_DRAW);

	// VAO
	glGenVertexArrays(1, &hVAO);
	glBindVertexArray(hVAO);

	// bind VBOs, input layout
	// 0, vertex pos
	glBindBuffer(GL_ARRAY_BUFFER, hBO[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(0));
	glEnableVertexAttribArray(0);

	// 1, vertex normal vector
	glBindBuffer(GL_ARRAY_BUFFER, hBO[0]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	// 2, texture coordinates
	glBindBuffer(GL_ARRAY_BUFFER, hBO[0]);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(sizeof(float) * 6));
	glEnableVertexAttribArray(2);

	// bind EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, hBO[1]);

	// end setting
	glBindVertexArray(0);
}

void WfObj::deleteHandles()
{
	if (hVAO != 0)
	{
		glDeleteVertexArrays(1, &hVAO);
		glDeleteBuffers(2, hBO.data());
		hVAO = 0;
	}
}

GLuint WfObj::gethVAO() const
{
	return hVAO;
}
