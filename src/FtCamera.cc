
#include "FtCamera.h"
#include <cmath>


FtCamera::FtCamera(t_FTMFLOAT4 const& startPos, t_FTMFLOAT4 const& startTarget,
	float const nearPlane, float const farPlane, float const aspectRatio, float const fov)
	: pos(startPos), target(startTarget), up(ftmf4_set_vector(0.0f, 1.0f, 0.0f, 0.0f)),
	distNear(nearPlane), distFar(farPlane), aspectRatio(aspectRatio), fov(fov)
{
}

FtCamera::~FtCamera() {}

// setter
void FtCamera::setPos(t_FTMFLOAT4 const& p)
{
	pos = p;
}

void FtCamera::setTarget(t_FTMFLOAT4 const& p)
{
	target = p;
}

void FtCamera::setAspectRatio(float const ar)
{
	aspectRatio = ar;
}

void FtCamera::setFov(float const f)
{
	fov = f;
}

t_FTMFLOAT4X4 FtCamera::getVMatrix() const
{
	return ftmf44_set_view(pos, target, up);
}

t_FTMFLOAT4X4 FtCamera::getPMatrix() const
{
	/*
	// DirectX Style, [0, 1]
	t_FTMFLOAT4X4 perspectiveMatrix = ftmf44_set_scale(ftmf4_set_vector(
		1.0f / (tanf(fov / 2) * aspectRatio),
		1.0f / tanf(fov / 2),
		distFar / (distFar - distNear),
		1.0f));
	perspectiveMatrix.data[2][3] = 1.0f;
	perspectiveMatrix.data[3][3] = 0.0f;
	perspectiveMatrix.data[3][2] = - (distFar * distNear) / (distFar - distNear);
	*/

	// OpenGL Style, [-1, 1]
	t_FTMFLOAT4X4 perspectiveMatrix = ftmf44_set_scale(ftmf4_set_vector(
		1.0f / (tanf(fov / 2) * aspectRatio),
		1.0f / tanf(fov / 2),
		(distFar + distNear) / (distFar - distNear),
		1.0f));
	perspectiveMatrix.data[2][3] = 1.0f;
	perspectiveMatrix.data[3][3] = 0.0f;
	perspectiveMatrix.data[3][2] = -2 * (distFar * distNear) / (distFar - distNear);
	return perspectiveMatrix;
}

t_FTMFLOAT4X4 FtCamera::getVPMatrix() const
{
	t_FTMFLOAT4X4 v = ftmf44_set_view(pos, target, up);
	t_FTMFLOAT4X4 p = getPMatrix();
	return ftmf44_mult(&v, &p);
}

void FtCamera::movePos(float const x, float const y, float const z)
{
	pos.data[0] += x;
	pos.data[1] += y;
	pos.data[2] += z;
}

void FtCamera::moveTarget(float const x, float const y, float const z)
{
	target.data[0] += x;
	target.data[1] += y;
	target.data[2] += z;
}

void FtCamera::zoom(float const dist)
{
	fov += dist;
}
