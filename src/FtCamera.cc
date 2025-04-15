
#include "FtCamera.h"
#include <cmath>

#include <iostream>

FtCamera::FtCamera(t_FTMFLOAT4 const& startPos,
	float const nearPlane, float const farPlane, float const aspectRatio, float const fov) :
	pos(startPos),
	front(ftmf4_set_vector(0.0f, 0.0f, 1.0f, 0.0f)),
	right(ftmf4_set_vector(1.0f, 0.0f, 0.0f, 0.0f)),
	up(ftmf4_set_vector(0.0f, 1.0f, 0.0f, 0.0f)),
	worldUp(ftmf4_set_vector(0.0f, 1.0f, 0.0f, 0.0f)),
	yaw(0.0f), pitch(0.0f),
	distNear(nearPlane), distFar(farPlane),
	aspectRatio(aspectRatio), fov(fov),
	rotOn(false)
{
}

FtCamera::~FtCamera() {}

// setter
void FtCamera::setPos(t_FTMFLOAT4 const& p)
{
	pos = p;
}

void FtCamera::setAngle(float const y, float const p)
{
	yaw = y;
	pitch = p;
	yaw = std::min(std::max(yaw, -YAW_LIMIT), YAW_LIMIT);
	pitch = std::min(std::max(pitch, -PITCH_LIMIT), PITCH_LIMIT);

	// update front
	float const yrad = yaw * M_PI / 180.0f;
	float const prad = pitch * M_PI / 180.0f;
	front = ftmf4_set_vector(-sinf(yrad) * cosf(prad), -sinf(prad), cosf(yrad) * cosf(prad), 0.0f);

	// get right using global up
	right = ftmf4_vcross(worldUp, front);

	// get up using up and front
	up = ftmf4_vcross(front, right);
}

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

void FtCamera::movePos(float const x, float const y, float const z)
{
	pos = ftmf4_vadd(ftmf4_vadd(ftmf4_vadd(pos,
		ftmf4_set_vector(x * right.data[0], x * right.data[1], x * right.data[2], 0.0f)),
		ftmf4_set_vector(y * up.data[0], y * up.data[1], y * up.data[2], 0.0f)),
		ftmf4_set_vector(z * front.data[0], z * front.data[1], z * front.data[2], 0.0f));
}

void FtCamera::moveAngle(float const dYaw, float const dPitch)
{
	yaw += dYaw;
	pitch += dPitch;
	yaw = std::min(std::max(yaw, -YAW_LIMIT), YAW_LIMIT);
	pitch = std::min(std::max(pitch, -PITCH_LIMIT), PITCH_LIMIT);

	// update front
	float const yrad = yaw * M_PI / 180.0f;
	float const prad = pitch * M_PI / 180.0f;
	front = ftmf4_set_vector(-sin(yrad) * cos(prad), -sin(prad), cos(yrad) * cos(prad), 0.0f);

	// get right using global up
	right = ftmf4_vcross(worldUp, front);

	// get up using up and front
	up = ftmf4_vcross(front, right);
}

void FtCamera::zoom(float const dist)
{
	fov += dist;
	fov = std::min(std::max(fov, MIN_FOV_LIMIT), MAX_FOV_LIMIT);
}

void FtCamera::resetPose()
{
	front = ftmf4_set_vector(0.0f, 0.0f, 1.0f, 0.0f);
	right = ftmf4_set_vector(1.0f, 0.0f, 0.0f, 0.0f);
	up = ftmf4_set_vector(0.0f, 1.0f, 0.0f, 0.0f);
	yaw = 0;
	pitch = 0;
}
