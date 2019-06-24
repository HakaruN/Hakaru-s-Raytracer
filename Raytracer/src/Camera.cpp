#include "Camera.h"
#include <math.h>
#include "Vector.h"

Camera::Camera(Vector origin, Vector target, Vector upGuide, double fov, double aspectRatio)
{
	//mForwards = Vector::vectorBetweenVectors(target, mOrigin);
	mOrigin = origin;
	mForwards = (target - origin).Normalise();
	mRight = mForwards.cross(upGuide).Normalise();
	mUp = mRight.cross(mForwards);

	maspectRatio = aspectRatio;

	mHeight = tan(fov);
	mWidth = mHeight * maspectRatio;
}


void Camera::update(Vector origin, Vector target, Vector upGuide, double fov, double aspectRatio)
{
	mOrigin = origin;
	mForwards = (target - origin).Normalise();
	mRight = mForwards.cross(upGuide).Normalise();
	mUp = mRight.cross(mForwards);

	maspectRatio = aspectRatio;

	mHeight = tan(fov);
	mWidth = mHeight * maspectRatio;
}