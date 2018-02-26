#include "camera.h"
#include "maths_funcs.h"
#include <iostream>
#include "stdio.h"
#include <GL/freeglut.h>

const double Camera::TO_RADS = 3.141592654 / 180.0;

Camera::Camera(int WindowWidth, int WindowHeight)
{
	windowWidth = WindowWidth;
	windowHeight = WindowHeight;
	pos = vec3(0.0f, 0.0f, 5.0f);
	target = vec3(0.0f, 0.0f, -1.0f);
	target = normalise(target);
	up = vec3(0.0f, 1.0f, 0.0f);

	Init();
}

void Camera::Init()
{
	ySens= 0.2; 
	xSens = 0.2;
	moveSpeed = 0.080f; 
	mouseSpeed = 0.003f;
	angleH = 3.14f;
	angleV = 0.0f;

	direction.v[0] = 0.0f;
	direction.v[1] = 0.0f;
	direction.v[2] = 1.0f;

	right.v[0] = sin(3.14f - (3.14f/2.0f));
	right.v[1] = 0.0f;
	right.v[2] = cos(0.0f - (3.14f/2.0f));

	wDown = false;
	sDown = false;
	aDown = false;
	dDown = false;
	shiftDown = false;
	ctrlDown = false;

	mousePos.v[0] = windowWidth / 2;
	mousePos.v[1] = windowHeight / 2;

	glutWarpPointer(mousePos.v[0], mousePos.v[1]);
}

const float Camera::toRads(const float &theAngleInDegrees) const
{
	return theAngleInDegrees * TO_RADS;
}

void Camera::movement()
{
	if (wDown)
	{
		pos += direction * moveSpeed;
	}

	if (sDown)	
	{
		pos -= direction * moveSpeed;
	}

	if (aDown) 
	{
		pos -= right * moveSpeed;
	}

	if (dDown)
	{
		pos += right * moveSpeed; 
	}

	if (shiftDown)
	{
		pos += vec3(0.0f, 0.02f, 0.0f);
	}

	if (ctrlDown)
	{
		pos += vec3(0.0f, -0.02f, 0.0f);
	}
}

void Camera::OnMouse(int x, int y)
{
	const int DeltaX = ((windowWidth / 2) - x); 
	const int DeltaY = ((windowHeight / 2) - y);

	mousePos.v[0] = x; 
	mousePos.v[1] = y;

	if (abs(DeltaX) > 1 || abs(DeltaY) > 1)
	{
		glutWarpPointer((windowWidth / 2), (windowHeight / 2));
	}

	angleH += (float)DeltaX * mouseSpeed;
	angleV += (float)DeltaY * mouseSpeed;


	if (angleV > 1.5708f)
	{
		angleV = 1.5708f;
	}
	if (angleV < -1.5708f)
	{
		angleV = -1.5708f;
	}

	direction.v[0] = cos(angleV) * sin(angleH);
	direction.v[1] = sin(angleV);
	direction.v[2] = cos(angleV) * cos(angleH);

	right.v[0] = sin(angleH - (3.14f / 2.0f));
	right.v[1] = 0.0f;
	right.v[2] = cos(angleH - (3.14f / 2.0f));

	up = cross(right, direction);
}