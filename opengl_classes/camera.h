#ifndef CAMERA_H
#define	CAMERA_H

#include "maths_funcs.h"

class Camera
{
public:
	static const double TO_RADS;

	const float toRads(const float &angleInDegrees) const;

	Camera(int WindowWidth, int WindowHeight);

	void movement();

	bool wDown;
	bool sDown;
	bool aDown;
	bool dDown;
	bool shiftDown;
	bool ctrlDown;

	void OnMouse(int x, int y);

	const vec3& GetPos() const
	{
		return pos;
	}

	const vec3& GetTarget() const
	{
		return target;
	}

	const vec3& GetUp() const
	{
		return up;
	}

	const vec3& GetRot() const
	{
		return rotation;
	}

	const vec3& GetDir() const
	{
		return direction;
	}

	const vec3& GetRight() const
	{
		return right;
	}

private:

	vec3 pos;
	vec3 target;
	vec3 up;

	vec2 mousePos;

	vec3 rotation;

	vec3 direction;
	vec3 right;

	float ySens;
	float xSens;
	float moveSpeed;
	float mouseSpeed;

	void Init();

	int windowWidth;
	int windowHeight;

	float angleH;
	float angleV;
};

#endif