
#ifndef FT_CAMERA_H
#define FT_CAMERA_H

extern "C"
{
#include "ft_math/ft_math.h"
}

class FtCamera
{
private:
	FtCamera() = delete;
	FtCamera(FtCamera const&) = delete;
	FtCamera& operator=(FtCamera const&) = delete;

	t_FTMFLOAT4 pos;
	t_FTMFLOAT4 const up;	// constant, (0, 1, 0, 0)

	float yaw;		// y axis
	float pitch;	// x axis

	float const distNear;
	float const distFar;

	float aspectRatio;
	float fov;

public:
	FtCamera(t_FTMFLOAT4 const& startPos,
		float const nearPlane, float const farPlane, float const aspectRatio, float const fov);
	~FtCamera();

	// setter
	void setPos(t_FTMFLOAT4 const& p);
	void setYaw(float const deg);
	void setPitch(float const deg);
	void setAspectRatio(float const ar);
	void setFov(float const f);

	t_FTMFLOAT4X4 getVMatrix() const;
	t_FTMFLOAT4X4 getPMatrix() const;
	t_FTMFLOAT4X4 getVPMatrix() const;

	void movePos(float const x, float const y, float const z);
	void moveYaw(float deg);
	void movePitch(float deg);
	void zoom(float const dist);
};

#endif
