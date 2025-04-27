
#include "FtCamera.h"
#include <cmath>

#include <iostream>

FtCamera::FtCamera(t_FTMFLOAT4 const& startPos,
	float const nearPlane, float const farPlane, float const aspectRatio, float const fov) :
	FtObj(startPos, 0.0f, 0.0f),
	distNear(nearPlane), distFar(farPlane),
	aspectRatio(aspectRatio), fov(fov),
	rotOn(false)
{
}

FtCamera::~FtCamera() {}

void FtCamera::setAspectRatio(float const ar)
{
	aspectRatio = ar;
}

void FtCamera::setFov(float const f)
{
	fov = f;
	fov = std::min(std::max(fov, MIN_FOV_LIMIT), MAX_FOV_LIMIT);
}

void FtCamera::setRot(bool stat)
{
	rotOn = stat;
}

t_FTMFLOAT4X4 FtCamera::getVMatrix() const
{
	t_FTMFLOAT4X4	result;

	*(t_FTMFLOAT4*)(result.data[2]) = front;
	*(t_FTMFLOAT4*)(result.data[0]) = right;
	*(t_FTMFLOAT4*)(result.data[1]) = up;
	result.data[0][3] = -ftmf4_vdot(pos, *(t_FTMFLOAT4*)(result.data[0]));
	result.data[1][3] = -ftmf4_vdot(pos, *(t_FTMFLOAT4*)(result.data[1]));
	result.data[2][3] = -ftmf4_vdot(pos, *(t_FTMFLOAT4*)(result.data[2]));
	result.data[3][0] = 0.0;
	result.data[3][1] = 0.0;
	result.data[3][2] = 0.0;
	result.data[3][3] = 1.0;
	ftmf44_transpose(&result);
	return result;
}

t_FTMFLOAT4X4 FtCamera::getPMatrix() const
{
	const float fovRad = fov * M_PI / 180.0f;
	/*
	// DirectX Style, [0, 1]
	t_FTMFLOAT4X4 perspectiveMatrix = ftmf44_set_scale(ftmf4_set_vector(
		1.0f / (tanf(fovRad * 0.5f) * aspectRatio),
		1.0f / tanf(fovRad * 0.5f),
		distFar / (distFar - distNear),
		1.0f));
	perspectiveMatrix.data[2][3] = 1.0f;
	perspectiveMatrix.data[3][3] = 0.0f;
	perspectiveMatrix.data[3][2] = -(distFar * distNear) / (distFar - distNear);
	*/

	// OpenGL Style, [-1, 1]
	t_FTMFLOAT4X4 perspectiveMatrix = ftmf44_set_scale(ftmf4_set_vector(
		1.0f / (tan(fovRad * 0.5f) * aspectRatio),
		1.0f / tan(fovRad * 0.5f),
		(distFar + distNear) / (distFar - distNear),
		1.0f));
	perspectiveMatrix.data[2][3] = 1.0f;
	perspectiveMatrix.data[3][3] = 0.0f;
	perspectiveMatrix.data[3][2] = (distFar * distNear) * -2.0f / (distFar - distNear);

	return perspectiveMatrix;
}

t_FTMFLOAT4X4 FtCamera::getVPMatrix() const
{
	t_FTMFLOAT4X4 v = getVMatrix();
	t_FTMFLOAT4X4 p = getPMatrix();
	return ftmf44_mult(&v, &p);
}

bool FtCamera::getRot() const
{
	return rotOn;
}

void FtCamera::zoom(float const dist)
{
	fov += dist;
	fov = std::min(std::max(fov, MIN_FOV_LIMIT), MAX_FOV_LIMIT);
}
