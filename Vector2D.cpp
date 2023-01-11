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
Vector2D::Vector2D(int w, int scr_w, float y)
{
	this->x = (float)(scr_w / 2 - w / 2);
	this->y = y;
}
Vector2D::Vector2D(float x, int h, int scr_h)
{
	this->x = x;
	this->y = (float)(scr_h / 2 - h / 2);
}
Vector2D::Vector2D(int w, int scr_w, int h, int scr_h)
{
	this->x = (float)(scr_w / 2 + w / 2);
	this->y = (float)(scr_h / 2 + h / 2);
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

Vector2D& Vector2D::add(const float& val)
{
	x += val;
	y += val;

	return *this;
}
Vector2D& Vector2D::sub(const float& val)
{
	x -= val;
	y -= val;

	return *this;
}
Vector2D& Vector2D::mul(const float& val)
{
	x *= val;
	y *= val;

	return *this;
}
Vector2D& Vector2D::div(const float& val)
{
	x /= val;
	y /= val;

	return *this;
}

float Vector2D::length()
{
	return sqrt(x * x + y * y);
}
Vector2D& Vector2D::normalize()
{
	float len = length();
	this->x /= len;
	this->y /= len;

	return *this;
}

Vector2D& operator+(Vector2D& vec1, const Vector2D& vec2)
{
	Vector2D aux = vec1;
	return aux.add(vec2);
}
Vector2D& operator-(Vector2D& vec1, const Vector2D& vec2)
{
	Vector2D aux = vec1;
	return aux.sub(vec2);
}
Vector2D& operator*(Vector2D& vec1, const Vector2D& vec2)
{
	Vector2D aux = vec1;
	return aux.mul(vec2);
}
Vector2D& operator/(Vector2D& vec1, const Vector2D& vec2)
{
	Vector2D aux = vec1;
	return aux.div(vec2);
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

Vector2D& operator+(Vector2D& vec1, const float& val)
{
	Vector2D aux = vec1;
	return aux.add(val);
}
Vector2D& operator-(Vector2D& vec1, const float& val)
{
	Vector2D aux = vec1;
	return aux.sub(val);
}
Vector2D& operator*(Vector2D& vec1, const float& val)
{
	Vector2D aux = vec1;
	return aux.mul(val);
}
Vector2D& operator/(Vector2D& vec1, const float& val)
{
	Vector2D aux = vec1;
	return aux.div(val);
}

Vector2D& Vector2D::operator+=(const float& val)
{
	return this->add(val);
}
Vector2D& Vector2D::operator-=(const float& val)
{
	return this->sub(val);
}
Vector2D& Vector2D::operator*=(const float& val)
{
	return this->mul(val);
}
Vector2D& Vector2D::operator/=(const float& val)
{
	return this->div(val);
}

std::ostream& operator<<(std::ostream& out, const Vector2D& vec)
{
	out << '(' << vec.x << ", " << vec.y << ')';
	return out;
}