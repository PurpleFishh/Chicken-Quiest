#pragma once
#include <iostream>

class Vector2D
{
public:
	float x, y;
	Vector2D();
	Vector2D(float x, float y);

	Vector2D& add(const Vector2D& vec);
	Vector2D& sub(const Vector2D& vec);
	Vector2D& mul(const Vector2D& vec);
	Vector2D& div(const Vector2D& vec);

	friend Vector2D& operator+(Vector2D& vec1, const Vector2D& vec2);
	friend Vector2D& operator-(Vector2D& vec1, const Vector2D& vec2);
	friend Vector2D& operator*(Vector2D& vec1, const Vector2D& vec2);
	friend Vector2D& operator/(Vector2D& vec1, const Vector2D& vec2);

	Vector2D& operator+=(const Vector2D& vec);
	Vector2D& operator-=(const Vector2D& vec);
	Vector2D& operator*=(const Vector2D& vec);
	Vector2D& operator/=(const Vector2D& vec);

	friend std::ostream& operator<<(std::ostream& out, const Vector2D& vec);
};