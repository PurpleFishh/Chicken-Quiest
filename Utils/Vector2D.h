#pragma once
#include <iostream>

class Vector2D
{
public:
	float x, y;
	Vector2D();
	Vector2D(float x, float y);
	Vector2D(int w, int scr_w, float y);
	Vector2D(float x, int h, int scr_h);
	Vector2D(int w, int scr_w, int h, int scr_h);

	Vector2D& add(const Vector2D& vec);
	Vector2D& sub(const Vector2D& vec);
	Vector2D& mul(const Vector2D& vec);
	Vector2D& div(const Vector2D& vec);

	Vector2D& add(const float& val);
	Vector2D& sub(const float& val);
	Vector2D& mul(const float& val);
	Vector2D& div(const float& val);

	double length();
	Vector2D& normalize();

	friend Vector2D& operator+(Vector2D& vec1, const Vector2D& vec2);
	friend Vector2D& operator-(Vector2D& vec1, const Vector2D& vec2);
	friend Vector2D& operator*(Vector2D& vec1, const Vector2D& vec2);
	friend Vector2D& operator/(Vector2D& vec1, const Vector2D& vec2);

	friend Vector2D& operator+(Vector2D& vec1, const float& val);
	friend Vector2D& operator-(Vector2D& vec1, const float& val);
	friend Vector2D& operator*(Vector2D& vec1, const float& val);
	friend Vector2D& operator/(Vector2D& vec1, const float& val);

	Vector2D& operator+=(const Vector2D& vec);
	Vector2D& operator-=(const Vector2D& vec);
	Vector2D& operator*=(const Vector2D& vec);
	Vector2D& operator/=(const Vector2D& vec);

	Vector2D& operator+=(const float& val);
	Vector2D& operator-=(const float& val);
	Vector2D& operator*=(const float& val);
	Vector2D& operator/=(const float& val);

	friend std::ostream& operator<<(std::ostream& out, const Vector2D& vec);
};