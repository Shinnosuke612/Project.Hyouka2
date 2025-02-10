#pragma once
#include "Struct.h"
#define _USE_MATH_DEFINES
#include "math.h"
#include <assert.h>

class Camera {
private:
	Vector2 pos_;
	Vector2 scale_;
	float theta_;
	Matrix3x3 vpvpMatrix_;

public:

	Camera();
	~Camera();

	Vector2 GetCameraPos() { return  pos_; }
	Vector2 GetCameraScale() { return  scale_; }
	float GetCameraTehta() { return theta_; }
	Matrix3x3 &GetvpvpMatrix() { return vpvpMatrix_; }

	Matrix3x3 MakeAffineMatrix(Vector2 scale, float rotate, Vector2 translate);

	Vector2 Transform(Vector2 vector, Matrix3x3 matrix);

	Matrix3x3 MakeOrthographicMatrix(float left, float top, float right, float bottom);

	Matrix3x3 MakeViewPortMatrix(float left, float top, float width, float height);

	Matrix3x3 Inverse3x3(Matrix3x3 matrix);

	Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2);
};

