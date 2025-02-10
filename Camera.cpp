#include "Camera.h"

Camera::Camera() {
	pos_ = { kPlayWindouWidth / 2,kWindowHeight / 2 };
	scale_ = { 1.0f,1.0f };
	theta_ = 0.0f;
	vpvpMatrix_ = { {0,0,0} };
}

Matrix3x3 Camera::MakeAffineMatrix(Vector2 scale, float rotate, Vector2 translate)
{
	Matrix3x3 result = {};

	result.m[0][0] = scale.x * float(cos(rotate));
	result.m[0][1] = scale.x * float(sin(rotate));
	result.m[0][2] = 0.0f;

	result.m[1][0] = scale.y * float(-sin(rotate));
	result.m[1][1] = scale.y * float(cos(rotate));
	result.m[1][2] = 0.0f;

	result.m[2][0] = translate.x;
	result.m[2][1] = translate.y;
	result.m[2][2] = 1.0f;

	return result;
}

Vector2 Camera::Transform(Vector2 vector, Matrix3x3 matrix)
{
	Vector2 result = {};
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
	float w = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];
	if (w == 0.0f) {
		w = 0.1f;
	}
	result.x /= w;
	result.y /= w;
	return result;
}

Matrix3x3 Camera::MakeOrthographicMatrix(float left, float top, float right, float bottom)
{

	Matrix3x3 result;

	result.m[0][0] = 2.0f / (right - left);
	result.m[0][1] = 0;
	result.m[0][2] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = 2.0f / (top - bottom);
	result.m[1][2] = 0;

	result.m[2][0] = (left + right) / (left - right);
	result.m[2][1] = (top + bottom) / (bottom - top);
	result.m[2][2] = 1;

	return result;
}

Matrix3x3 Camera::MakeViewPortMatrix(float left, float top, float width, float height)
{

	Matrix3x3 result;

	result.m[0][0] = width / 2.0f;
	result.m[0][1] = 0;
	result.m[0][2] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = -height / 2.0f;
	result.m[1][2] = 0;

	result.m[2][0] = left + width / 2.0f;
	result.m[2][1] = top + height / 2.0f;
	result.m[2][2] = 1;

	return result;
}

Matrix3x3 Camera::Inverse3x3(Matrix3x3 matrix)
{

	Matrix3x3 result;

	float determinant = matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2] +
		matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0] +
		matrix.m[1][2] * matrix.m[2][0] * matrix.m[2][1] -
		matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0] -
		matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2] -
		matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1];

	determinant = 1.0f / determinant;

	result.m[0][0] = (matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1]) * determinant;
	result.m[0][1] = -(matrix.m[0][1] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][1]) * determinant;
	result.m[0][2] = (matrix.m[0][1] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][1]) * determinant;

	result.m[1][0] = -(matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][0]) * determinant;
	result.m[1][1] = (matrix.m[0][0] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][0]) * determinant;
	result.m[1][2] = -(matrix.m[0][0] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][0]) * determinant;

	result.m[2][0] = (matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0]) * determinant;
	result.m[2][1] = -(matrix.m[0][0] * matrix.m[2][1] - matrix.m[0][1] * matrix.m[2][0]) * determinant;
	result.m[2][2] = (matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0]) * determinant;

	return result;
}

Matrix3x3 Camera::Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2)
{
	Matrix3x3 result = {};

	result.m[0][0] = matrix1.m[0][0] * matrix2.m[0][0] + matrix1.m[0][1] * matrix2.m[1][0] + matrix1.m[0][2] * matrix2.m[2][0];
	result.m[0][1] = matrix1.m[0][0] * matrix2.m[0][1] + matrix1.m[0][1] * matrix2.m[1][1] + matrix1.m[0][2] * matrix2.m[2][1];
	result.m[0][2] = matrix1.m[0][0] * matrix2.m[0][2] + matrix1.m[0][1] * matrix2.m[1][2] + matrix1.m[0][2] * matrix2.m[2][2];
	result.m[1][0] = matrix1.m[1][0] * matrix2.m[0][0] + matrix1.m[1][1] * matrix2.m[1][0] + matrix1.m[1][2] * matrix2.m[2][0];
	result.m[1][1] = matrix1.m[1][0] * matrix2.m[0][1] + matrix1.m[1][1] * matrix2.m[1][1] + matrix1.m[1][2] * matrix2.m[2][1];
	result.m[1][2] = matrix1.m[1][0] * matrix2.m[0][2] + matrix1.m[1][1] * matrix2.m[1][2] + matrix1.m[1][2] * matrix2.m[2][2];
	result.m[2][0] = matrix1.m[2][0] * matrix2.m[0][0] + matrix1.m[2][1] * matrix2.m[1][0] + matrix1.m[2][2] * matrix2.m[2][0];
	result.m[2][1] = matrix1.m[2][0] * matrix2.m[0][1] + matrix1.m[2][1] * matrix2.m[1][1] + matrix1.m[2][2] * matrix2.m[2][1];
	result.m[2][2] = matrix1.m[2][0] * matrix2.m[0][2] + matrix1.m[2][1] * matrix2.m[1][2] + matrix1.m[2][2] * matrix2.m[2][2];

	return result;
}
