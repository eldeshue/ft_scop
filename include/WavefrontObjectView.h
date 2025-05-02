
#ifndef WAVEFRONT_OBJECT_VIEW_H
#define WAVEFRONT_OBJECT_VIEW_H

#include <glad/glad.h>

#include "WavefrontObject.h"
#include "FTObj.h"

// view of WfObj
class WfObjView : public FtObj
{
private:
	WfObjView() = delete;

	float scale;

	WfObj const* source;
	GLuint hShader;
	GLuint hTexture;

	GLint mvpMatUniformLoc;

public:
	WfObjView(t_FTMFLOAT4 const& startPos, float const startYaw, float const startPitch,
		float const scale, WfObj const* source, GLuint hs, GLuint ht);
	WfObjView(WfObjView const& other);
	~WfObjView();

	WfObjView& operator=(WfObjView const& rhs);

	GLuint getShader() const;
	void setShader(GLuint hNewShader);

	// get model matrix from position and pose
	t_FTMFLOAT4X4 getMMatrix() const;

	void draw(t_FTMFLOAT4X4 const& vp) const;	// need shader, need texture
};

#endif
