
#ifndef WAVEFRONT_OBJECT_H
#define WAVEFRONT_OBJECT_H

#include <vector>
#include <array>
#include <string>
#include <glad/glad.h>

using Float3 = std::array<float, 3>;
using Float2 = std::array<float, 2>;

using VecF3 = std::vector<Float3>;
using VecF2 = std::vector<Float2>;

// created by parser
class WfObj
{
private:
	WfObj(WfObj const&) = delete;
	WfObj& operator=(WfObj const&) = delete;	// non copyable

	// name of the file
	std::string const name;

	// buffer
	VecF3 vPosBuf;
	VecF3 vNormVecBuf;
	VecF2 tPosBuf;
	std::vector<uint32_t> indexBuf;

	// handles
	std::array<GLuint, 4> bOB;
	GLuint hVAO;

public:
	WfObj(std::string const& name);
	~WfObj();

	// get
	VecF3& getVPosBuffer();
	VecF3& getNVecBuffer();
	VecF2& getTexPosBuffer();
	std::vector<uint32_t>& getIdxBuffer();
	size_t getIdxBufferSize() const;

	// init handles
	void initHandles();
	void deleteHandles();	// must be called before destruction

	GLuint gethVAO() const;
};

#endif
