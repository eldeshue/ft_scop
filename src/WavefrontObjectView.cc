
#include "WavefrontObjectView.h"

WfObjView::WfObjView(t_FTMFLOAT4 const& startPos, float const startYaw, float const startPitch,
	float const scale, WfObj const* source, GLuint hs, GLuint ht) :
	FtObj(startPos, startYaw, startPitch),
	scale(scale),
	source(source),
	hShader(hs),
	hTexture(ht),
	mvpMatUniformLoc(glGetUniformLocation(hShader, "mvp"))
{
}

WfObjView::WfObjView(WfObjView const& other) :
	FtObj(other),
	scale(other.scale),
	source(other.source),
	hShader(other.hShader),
	hTexture(other.hTexture),
	mvpMatUniformLoc(other.mvpMatUniformLoc)
{
}

WfObjView::~WfObjView() {}

WfObjView& WfObjView::operator=(WfObjView const& rhs)
{
	if (this != &rhs)
	{
		static_cast<FtObj>(*this) = static_cast<FtObj>(rhs);
		scale = rhs.scale;
		source = rhs.source;
		hShader = rhs.hShader;
		hTexture = rhs.hTexture;
	}
	return *this;
}

// get model matrix from position and pose
t_FTMFLOAT4X4 WfObjView::getMMatrix() const
{
	t_FTMFLOAT4 scaleVector = ftmf4_set_vector(this->scale, this->scale, this->scale, 1.0f);
	t_FTMFLOAT4X4 modelMatrix = ftmf4_qtom(this->qOrigin);


	ftmf44_scale(&scaleVector, &modelMatrix);
	for (int i = 0; i < 3; ++i)
		modelMatrix.data[3][i] = this->pos.data[i];
	modelMatrix.data[3][3] = 1.0f;
	return modelMatrix;
}

void WfObjView::draw(t_FTMFLOAT4X4 const& vp) const
{
	t_FTMFLOAT4X4 m = getMMatrix();
	t_FTMFLOAT4X4 mvp = ftmf44_mult(&m, &vp);

	glUseProgram(hShader);
	glUniformMatrix4fv(mvpMatUniformLoc, 1, GL_FALSE, mvp.data[0]);
	glBindTexture(GL_TEXTURE_2D, hTexture);
	glBindVertexArray(this->source->gethVAO());		// bind VAO
	glDrawElements(GL_TRIANGLES, this->source->getIdxBufferSize(), GL_UNSIGNED_INT, 0);	// topology, size, type, start offset
	glBindVertexArray(0);		// bind VAO
}
