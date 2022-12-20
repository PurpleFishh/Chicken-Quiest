#include "Vector2D.h"

Vector2D::Vector2D()
{
	x = 0;
	y = 0;
}
Vector2D::Vector2D(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2D& Vector2D::add(const Vector2D& vec)
{
	x += vec.x;
	y += vec.y;

	return *this;
}
Vector2D& Vector2D::sub(const Vector2D& vec)
{
	x -= vec.x;
	y -= vec.y;

	return *this;
}
Vector2D& Vector2D::mul(const Vector2D& vec)
{
	x *= vec.x;
	y *= vec.y;

	return *this;
}
Vector2D& Vector2D::div(const Vector2D& vec)
{
	x /= vec.x;
	y /= vec.y;

	return *this;
}

Vector2D& operator+(Vector2D& vec1, const Vector2D& vec2)
{
	return vec1.add(vec2);
}
Vector2D& operator-(Vector2D& vec1, const Vector2D& vec2)
{
	return vec1.sub(vec2);
}
Vector2D& operator*(Vector2D& vec1, const Vector2D& vec2)
{
	return vec1.mul(vec2);
}
Vector2D& operator/(Vector2D& vec1, const Vector2D& vec2)
{
	return vec1.div(vec2);
}

Vector2D& Vector2D::operator+=(const Vector2D& vec)
{
	return this->add(vec);
}
Vector2D& Vector2D::operator-=(const Vector2D& vec)
{
	return this->sub(vec);
}
Vector2D& Vector2D::operator*=(const Vector2D& vec)
{
	return this->mul(vec);
}
Vector2D& Vector2D::operator/=(const Vector2D& vec)
{
	return this->div(vec);
}

std::ostream& operator<<(std::ostream& out, const Vector2D& vec)
{
	out << '(' << vec.x << ", " << vec.y << ')';
	return out;
}