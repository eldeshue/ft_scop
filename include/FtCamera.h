
#ifndef FT_CAMERA_H
#define FT_CAMERA_H

extern "C"
{
#include "ft_math/ft_math.h"
}

#define MAX_FOV_LIMIT 60.0f
#define MIN_FOV_LIMIT 20.0f

#include "FTObj.h"

class FtCamera : public FtObj
{
private:
	FtCamera() = delete;
	FtCamera(FtCamera const&) = delete;
	FtCamera& operator=(FtCamera const&) = delete;

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
	void setAspectRatio(float const ar);
	void setFov(float const f);
	void setRot(bool stat);

	t_FTMFLOAT4X4 getVMatrix() const;
	t_FTMFLOAT4X4 getPMatrix() const;
	t_FTMFLOAT4X4 getVPMatrix() const;
	bool getRot() const;

	void zoom(float const dist);
};

#endif
