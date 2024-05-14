#pragma once

#include <cmath>

namespace ys::math
{
	constexpr double kPi = 3.14159265358979;

	struct Vector2
	{
		float x;
		float y;

		static Vector2 One;
		static Vector2 Zero;
		static Vector2 Right;
		static Vector2 Left;
		static Vector2 Up;
		static Vector2 Down;

		Vector2() : x(0.0f), y(0.0f) {}

		Vector2(float x_, float y_) : x(x_), y(y_) {}

		Vector2 operator+(const float& scalar) const { return Vector2(x + scalar, y + scalar); }
		Vector2 operator-(const float& scalar) const { return Vector2(x - scalar, y - scalar); }
		Vector2 operator*(const float& scalar) const { return Vector2(x * scalar, y * scalar); }
		Vector2 operator/(const float& scalar) const { return Vector2(x / scalar, y / scalar); }
		
		Vector2 operator+(const Vector2& other) const { return Vector2(x + other.x, y + other.y); }
		Vector2 operator-(const Vector2& other) const { return Vector2(x - other.x, y - other.y); }
	};


	static bool circlePointCollide(const Vector2& center, const float& radius, const Vector2& point)
	{
		if (sqrt(pow((point.x - center.x), 2) + pow((point.y - center.y), 2)) <= radius)
			return true;
		return false;
	}



}
