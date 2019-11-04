#pragma once


class Camera3D
{
public:
	static const double PI;
	double x, y, z;
	double h, p, b;

	double fov, nearZ, farZ;

	Camera3D();
	void initialize(void);
	void setUpCameraProjection(void);
	void setUpCameraTransformation(void);

	void getForwardVector(double& vx, double& vy, double& vz);
};

