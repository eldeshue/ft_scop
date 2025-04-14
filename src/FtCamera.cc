
#include "FtCamera.h"
#include <cmath>


FtCamera::FtCamera(t_FTMFLOAT4 const& startPos,
	float const nearPlane, float const farPlane, float const aspectRatio, float const fov)
	: pos(startPos), up(ftmf4_set_vector(0.0f, 1.0f, 0.0f, 0.0f)), yaw(0.0f), pitch(0.0f),
	distNear(nearPlane), distFar(farPlane), aspectRatio(aspectRatio), fov(fov)
{
}

FtCamera::~FtCamera() {}

// setter
void FtCamera::setPos(t_FTMFLOAT4 const& p)
{
	pos = p;
}

void FtCamera::setYaw(float const deg)
{
	yaw = deg;
	yaw = std::min(std::max(yaw, -89.0f), 89.0f);
}

void FtCamera::setPitch(float const deg)
{
	pitch += deg;
	pitch = std::min(std::max(pitch, -89.0f), 89.0f);
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
	t_FTMFLOAT4X4	result;

	float const y = yaw * M_PI / 180.0f;
	float const p = pitch * M_PI / 180.0f;
	*(t_FTMFLOAT4*)(result.data[2]) = ftmf4_set_vector(-sinf(y) * cosf(p), -sinf(p), cosf(y) * cosf(p), 1.0f);
	ftmf4_vnormalize((t_FTMFLOAT4*)(result.data[2]));
	*(t_FTMFLOAT4*)(result.data[0])
		= ftmf4_vcross(up, *(t_FTMFLOAT4*)(result.data[2]));
	ftmf4_vnormalize((t_FTMFLOAT4*)(result.data[0]));
	*(t_FTMFLOAT4*)(result.data[1])
		= ftmf4_vcross(*(t_FTMFLOAT4*)(result.data[2]),
			*(t_FTMFLOAT4*)(result.data[0]));
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
		1.0f / (tanf(fovRad / 2) * aspectRatio),
		1.0f / tanf(fovRad / 2),
		distFar / (distFar - distNear),
		1.0f));
	perspectiveMatrix.data[2][3] = 1.0f;
	perspectiveMatrix.data[3][3] = 0.0f;
	perspectiveMatrix.data[3][2] = - (distFar * distNear) / (distFar - distNear);
	*/

	// OpenGL Style, [-1, 1]
	t_FTMFLOAT4X4 perspectiveMatrix = ftmf44_set_scale(ftmf4_set_vector(
		1.0f / (tanf(fovRad / 2) * aspectRatio),
		1.0f / tanf(fovRad / 2),
		(distFar + distNear) / (distFar - distNear),
		1.0f));
	perspectiveMatrix.data[2][3] = 1.0f;
	perspectiveMatrix.data[3][3] = 0.0f;
	perspectiveMatrix.data[3][2] = -2 * (distFar * distNear) / (distFar - distNear);
	return perspectiveMatrix;
}

t_FTMFLOAT4X4 FtCamera::getVPMatrix() const
{
	t_FTMFLOAT4X4 v = getVMatrix();
	t_FTMFLOAT4X4 p = getPMatrix();
	return ftmf44_mult(&v, &p);
}

void FtCamera::movePos(float const x, float const y, float const z)
{
	pos.data[0] += x;
	pos.data[1] += y;
	pos.data[2] += z;
}

void FtCamera::moveYaw(float deg)
{
	yaw += deg;
	yaw = std::min(std::max(yaw, -89.0f), 89.0f);
}

void FtCamera::movePitch(float deg)
{
	pitch += deg;
	pitch = std::min(std::max(pitch, -89.0f), 89.0f);
}

void FtCamera::zoom(float const dist)
{
	fov += dist;
}
