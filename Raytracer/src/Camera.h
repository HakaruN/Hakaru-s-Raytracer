#pragma once
#include "Vector.h"
class Camera
{
public:
	Camera(Vector origin, Vector target, Vector upGuide, double fov, double aspectRatio);
	void update(Vector origin, Vector target, Vector upGuide, double fov, double aspectRatio);

	Vector mOrigin;
	Vector mForwards;
	Vector mUp;
	Vector mRight;
	double mWidth, mHeight;
	double maspectRatio;
private:
};