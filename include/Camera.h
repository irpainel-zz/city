/*
 * Camera.h
 *
 *  Created on: Oct 8, 2014
 *      Author: Iury Roger Painelli
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "GlutFramework.h"
#include "glm/glm.hpp"

class Camera {
public:
	Camera();
	virtual ~Camera();
	void Refresh();
	void SetPos(float x, float y, float z);
    void GetPos(float &x, float &y, float &z);
    void GetDirectionVector(float &x, float &y, float &z);
	void SetYaw(float angle);
	void SetPitch(float angle);

	// Navigation
	void Move(float incr);
	void Strafe(float incr);
	void Fly(float incr);
	void RotateYaw(float angle);
	void RotatePitch(float angle);

private:
	float m_x, m_y, m_z;   // Position
    float m_lx, m_ly, m_lz; // Direction vector of where we are looking at
	float m_yaw, m_pitch; // Various rotation angles
	float m_strafe_lx, m_strafe_lz; // Always 90 degree to direction vector

	// Movement settings
	float translation_speed;
	float rotation_speed;
};

#endif /* CAMERA_H_ */
