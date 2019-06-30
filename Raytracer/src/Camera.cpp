#include <math.h>
#include "Maths\Maths.h"
#include "Camera.h"
#include "Maths\Vector.h"

Camera::Camera(Vector origin, Vector target, Vector upGuide, double fov, double aspectRatio)
{
	//mForwards = Vector::vectorBetweenVectors(target, mOrigin);
	mFov = fov;
	mOrigin = origin;
	mForwards = (target - origin).Normalise();
	mRight = mForwards.cross(upGuide).Normalise();
	mUp = mRight.cross(mForwards);

	maspectRatio = aspectRatio;

	mHeight = tan(Maths::degToRad(mFov));
	mWidth = mHeight * maspectRatio;
}


void Camera::update(Vector origin, Vector target, Vector upGuide, double fov, double aspectRatio)
{
	mFov = fov;
	mOrigin = origin;
	mForwards = (target - origin).Normalise();
	mRight = mForwards.cross(upGuide).Normalise();
	mUp = mRight.cross(mForwards);

	maspectRatio = aspectRatio;

	mHeight = tan( Maths::degToRad(mFov));
	mWidth = mHeight * maspectRatio;
}