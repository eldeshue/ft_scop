
#include "FTObj.h"
#include <cmath>

FtObj::FtObj(t_FTMFLOAT4 const& startPos, float const startYaw, float const startPitch) :
	pos(startPos),
	front(ftmf4_set_vector(0.0f, 0.0f, 1.0f, 0.0f)),
	right(ftmf4_set_vector(1.0f, 0.0f, 0.0f, 0.0f)),
	up(ftmf4_set_vector(0.0f, 1.0f, 0.0f, 0.0f)),
	qOrigin(ftmf4_set_id()),
	pitch(0.0f)
{
	// rotate by start yaw and start pitch
	moveAngle(startYaw, startPitch);
}

FtObj::FtObj(FtObj const& other) :
	pos(other.pos),
	front(other.front),
	right(other.right),
	up(other.up),
	qOrigin(other.qOrigin),
	pitch(other.pitch)
{
}

FtObj::~FtObj() {}

FtObj& FtObj::operator=(FtObj const& rhs)
{
	if (this != &rhs)
	{
		this->pos = rhs.pos;
		this->front = rhs.front;
		this->right = rhs.right;
		this->up = rhs.up;
		this->qOrigin = rhs.qOrigin;
		this->pitch = rhs.pitch;
	}
	return (*this);
}

// setter
void FtObj::setPos(t_FTMFLOAT4 const& p)
{
	pos = p;
}

void FtObj::setAngle(float const y, float const p)
{
	pitch = 0;
	qOrigin = ftmf4_set_id();
	moveAngle(y, p);
}

void FtObj::movePos(float const x, float const y, float const z)
{
	pos = ftmf4_vadd(ftmf4_vadd(ftmf4_vadd(pos,
		ftmf4_set_vector(x * right.data[0], x * right.data[1], x * right.data[2], 0.0f)),
		ftmf4_set_vector(y * up.data[0], y * up.data[1], y * up.data[2], 0.0f)),
		ftmf4_set_vector(z * front.data[0], z * front.data[1], z * front.data[2], 0.0f));
}

void FtObj::moveAngle(float const dYaw, float const dPitch)
{
	static t_FTMFLOAT4 const baseUp = ftmf4_set_vector(0.0f, 1.0f, 0.0f, 0.0f);
	static t_FTMFLOAT4 const baseFront = ftmf4_set_vector(0.0f, 0.0f, 1.0f, 0.0f);

	float const y = dYaw * M_PI / 180.0f;

	float const prevPitch = this->pitch;
	this->pitch = std::max(std::min(this->pitch + dPitch, PITCH_LIMIT), -PITCH_LIMIT);
	float const p = (this->pitch - prevPitch) * M_PI / 180.0f;

	t_FTMFLOAT4 qYaw = ftmf4_set_rodrigues(y, baseUp);
	qOrigin = ftmf4_qmult(qYaw, qOrigin);
	ftmf4_qnormalize(&qOrigin);

	t_FTMFLOAT4 tempFront = baseFront;
	ftmf4_qrotate(&tempFront, qOrigin);

	right = ftmf4_vcross(baseUp, tempFront);
	ftmf4_vnormalize(&right);

	t_FTMFLOAT4 qPitch = ftmf4_set_rodrigues(p, right);
	qOrigin = ftmf4_qmult(qPitch, qOrigin);
	ftmf4_qnormalize(&qOrigin);

	up = baseUp;
	ftmf4_qrotate(&up, qOrigin);
	front = baseFront;
	ftmf4_qrotate(&front, qOrigin);
}

void FtObj::resetPose()
{
	front = ftmf4_set_vector(0.0f, 0.0f, 1.0f, 0.0f);
	right = ftmf4_set_vector(1.0f, 0.0f, 0.0f, 0.0f);
	up = ftmf4_set_vector(0.0f, 1.0f, 0.0f, 0.0f);
	qOrigin = ftmf4_set_id();
	pitch = 0.0f;
}
