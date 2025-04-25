
#ifndef FT_OBJ_H
#define FT_OBJ_H

extern "C"
{
#include "ft_math/ft_math.h"
}

#define PITCH_LIMIT 85.0f

class FtObj
{
private:
	FtObj() = delete;
	FtObj(FtObj const&) = delete;
	FtObj& operator=(FtObj const&) = delete;

protected:
	t_FTMFLOAT4 pos;
	t_FTMFLOAT4 front;
	t_FTMFLOAT4 right;
	t_FTMFLOAT4 up;
	t_FTMFLOAT4 qOrigin;

	float pitch;

public:
	FtObj(t_FTMFLOAT4 const& startPos, float const startYaw, float const startPitch);
	~FtObj();

	// setter
	void setPos(t_FTMFLOAT4 const& p);
	void setAngle(float const y, float const p);

	// camera control
	void resetPose();

	void movePos(float const x, float const y, float const z);
	void moveAngle(float const dYaw, float const dPitch);
};

#endif
