
#ifndef WAVEFRONT_OBJECT_H
#define WAVEFRONT_OBJECT_H

#include <vector>
#include <array>
#include <string>
#include <glad/glad.h>

struct Vertex {
	float px, py, pz;
	float vnx, vny, vnz;
	float tx, ty;
};

// created by parser
class WfObj
{
private:
	WfObj(WfObj const&) = delete;
	WfObj& operator=(WfObj const&) = delete;	// non copyable

	// name of the file
	std::string const name;

	// buffer
	std::vector<Vertex> vertexBuf;
	std::vector<uint32_t> indexBuf;

	// handles
	GLuint hVAO;
	std::array<GLuint, 2> hBO;

public:
	WfObj(std::string const& name);
	~WfObj();

	// get
	std::vector<Vertex>& getVtxBuffer();
	std::vector<uint32_t>& getIdxBuffer();
	size_t getIdxBufferSize() const;

	// init handles
	void initHandles();
	void deleteHandles();	// must be called before destruction

	GLuint gethVAO() const;
};

#endif
