#ifndef PERSPECTIVECAMERA_H
#define PERSPECTIVECAMERA_H

// A type of camera, 

#include "../camera.h"
#include "../../math/matrix_util.h"
#include "../../math/vector3f.h"

class PerspectiveCamera : public Camera
{
private:
	float fov, n, f;
	int width, height;

	Vector3f target, up;
public:
	PerspectiveCamera(float fov, int width, int height, float n, float f) 
	{
		this->translation = Vector3f(0, 0, 0);
		this->direction = Vector3f(0, 0, 1);
		this->up = Vector3f(0, 1, 0);
		this->target = Vector3f(0, 0, 0);

		this->fov = fov;
		this->n = n;
		this->f = f;
		this->width = width;
		this->height = height;
	}

	Vector3f getUpVector()
	{
		return up;
	}

	void setUpVector(Vector3f up)
	{
		this->up.set(up);
	}

	virtual void updateCameraLogic()
	{
	}

	void updateCameraMatrices()
	{
		target.set(translation);
		target.add(direction);

		MatrixUtil::setToLookAt(viewMatrix, this->translation, this->target, this->up);
		MatrixUtil::setToProjection(projectionMatrix, this->fov, this->width, this->height, this->n, this->f);

		viewProjectionMatrix.set(viewMatrix);
		viewProjectionMatrix.multiply(projectionMatrix);
	}
};

#endif