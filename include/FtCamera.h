
#ifndef FT_CAMERA_H
#define FT_CAMERA_H

extern "C"
{
#include "ft_math/ft_math.h"
}

#define PITCH_LIMIT 85.0f

#define MAX_FOV_LIMIT 60.0f
#define MIN_FOV_LIMIT 20.0f

class FtCamera
{
private:
	FtCamera() = delete;
	FtCamera(FtCamera const&) = delete;
	FtCamera& operator=(FtCamera const&) = delete;

	t_FTMFLOAT4 pos;
	t_FTMFLOAT4 front;
	t_FTMFLOAT4 right;
	t_FTMFLOAT4 up;
	t_FTMFLOAT4 qOrigin;

	float pitch;
	float const distNear;
	float const distFar;

	float aspectRatio;
	float fov;
	bool rotOn;

public:
	FtCamera(t_FTMFLOAT4 const& startPos,
		float const nearPlane, float const farPlane, float const aspectRatio, float const fov);
	~FtCamera();

	// setter
	void setPos(t_FTMFLOAT4 const& p);
	void setAngle(float const y, float const p);
	void setAspectRatio(float const ar);
	void setFov(float const f);
	void setRot(bool stat);

	t_FTMFLOAT4X4 getVMatrix() const;
	t_FTMFLOAT4X4 getPMatrix() const;
	t_FTMFLOAT4X4 getVPMatrix() const;
	bool getRot() const;

	// camera control
	void resetPose();

	void movePos(float const x, float const y, float const z);
	void moveAngle(float const dYaw, float const dPitch);
	void zoom(float const dist);
};

#endif
