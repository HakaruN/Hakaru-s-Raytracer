#pragma once
#include "Maths\Vector.h"
class Camera
{
public:
	Camera(Vector origin, Vector target, Vector upGuide, double fov, double aspectRatio);
	void update(Vector origin, Vector target, Vector upGuide, double fov, double aspectRatio);

	Vector mOrigin;
	Vector mForwards;
	Vector mUp;
	Vector mRight;
	Vector camLook;
	double mWidth, mHeight;
	double maspectRatio;
	double mFov;
private:
};