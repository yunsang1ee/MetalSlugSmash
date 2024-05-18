#pragma once

#include <cmath>

namespace ys::math
{
	constexpr float kPi = 3.14159265358979;

	struct Vector2
	{
		float x;
		float y;

		static Vector2 Rotate(Vector2 vector, const float& degree)
		{
			float radian{ (degree / 180.0f) * kPi };
			vector.nomalize();
			auto x = cosf(radian) * vector.x - sinf(radian) * vector.y;
			auto y = sinf(radian) * vector.x + cosf(radian) * vector.y;
			return Vector2(x, y);
		}
		//nomalize한 vector를 넣어서 계산하면 cos@
		static float Dot(Vector2& vec1, Vector2& vec2) { return vec1.x * vec2.x + vec1.y * vec2.y; }
		static float Cross(Vector2& vec1, Vector2& vec2) { return vec1.x * vec2.y - vec1.y * vec2.x; }

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
		
		Vector2 operator*(const Vector2& other) const { return Vector2(x * other.x, y * other.y); }
		Vector2 operator+(const Vector2& other) const { return Vector2(x + other.x, y + other.y); }
		Vector2 operator-(const Vector2& other) const { return Vector2(x - other.x, y - other.y); }

		float scalar() { return sqrtf(x * x + y * y); }
		Vector2 nomalize() 
		{ 
			auto len = scalar();
			x /= len;
			y /= len;
			return *this;
		}
	};
}
