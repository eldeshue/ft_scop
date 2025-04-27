
#include "WavefrontObject.h"


WfObj::WfObj(std::string const& name) :
	name(name),
	vPosBuf(),
	vNormVecBuf(),
	tPosBuf(),
	indexBuf(),
	hVAO(0)
{
	std::fill(bOB.begin(), bOB.end(), 0);
}

WfObj::~WfObj()
{
	glDeleteVertexArrays(1, &hVAO);
	glDeleteBuffers(4, bOB.data());
}

// get
VecF3& WfObj::getVPosBuffer()
{
	return vPosBuf;
}

VecF3& WfObj::getNVecBuffer()
{
	return vNormVecBuf;
}

VecF2& WfObj::getTexPosBuffer()
{
	return tPosBuf;
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
	glDeleteVertexArrays(1, &hVAO);
	glDeleteBuffers(4, bOB.data());

	// create new handles
	// create buffer objects
	glGenBuffers(4, bOB.data());

	// Vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, bOB[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Float3) * vPosBuf.size(), vPosBuf.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, bOB[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Float3) * vNormVecBuf.size(), vNormVecBuf.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, bOB[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Float2) * tPosBuf.size(), tPosBuf.data(), GL_STATIC_DRAW);

	// EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bOB[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * indexBuf.size(), indexBuf.data(), GL_STATIC_DRAW);

	// VAO
	glGenVertexArrays(1, &hVAO);
	glBindVertexArray(hVAO);

	// bind VBOs, input layout
	// 0, vertex pos
	glBindBuffer(GL_ARRAY_BUFFER, bOB[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Float3), reinterpret_cast<void*>(0));
	glEnableVertexAttribArray(0);

	// 1, vertex normal vector
	glBindBuffer(GL_ARRAY_BUFFER, bOB[1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Float3), reinterpret_cast<void*>(0));
	glEnableVertexAttribArray(1);

	// 2, texture coordinates
	glBindBuffer(GL_ARRAY_BUFFER, bOB[2]);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Float2), reinterpret_cast<void*>(0));
	glEnableVertexAttribArray(2);

	// bind EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bOB[3]);

	// end setting
	glBindVertexArray(0);
}

GLuint WfObj::gethVAO() const
{
	return hVAO;
}
