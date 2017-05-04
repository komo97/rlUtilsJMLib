#include "rlVector2.h"
#include <math.h>


rlVector2::rlVector2()
{
}

rlVector2::rlVector2(const float & _x, const float & _y)
{
	x = _x;
	y = _y;
}

int rlVector2::getX()
{
	return roundf(x);
}

int rlVector2::getY()
{
	return roundf(y);
}

float rlVector2::getXf()
{
	return x;
}

float rlVector2::getYf()
{
	return y;
}

void rlVector2::setX(const float & _x)
{
	x = _x;
}

void rlVector2::setY(const float & _y)
{
	y = _y;
}

void rlVector2::moveX(const float & _x)
{
	x += _x;
}

void rlVector2::moveY(const float & _y)
{
	y += _y;
}

void rlVector2::Translate(rlVector2 & vec)
{
	moveX(vec.getXf());
	moveY(vec.getYf());
}

rlVector2::~rlVector2()
{
}

rlVector2 & rlVector2::operator+=(rlVector2 rhs)
{
	return *this + rhs;
}

rlVector2 & rlVector2::operator-=(rlVector2 rhs)
{
	
	return *this - rhs;
}

float rlVector2::operator*=(rlVector2  rhs)
{
	return *this * rhs;
}

rlVector2 & rlVector2::operator*=(const float& rhs)
{

	return *this * rhs;
}

rlVector2 & operator+(rlVector2 lhs, rlVector2 rhs)
{
	lhs.setX(lhs.getXf() + rhs.getXf());
	lhs.setY(lhs.getYf() + rhs.getYf());
	return lhs;
}

rlVector2 & operator-(rlVector2 lhs, rlVector2 rhs)
{
	lhs.setX(lhs.getXf() - rhs.getXf());
	lhs.setY(lhs.getYf() - rhs.getYf());
	return lhs;
}

float operator*(rlVector2 lhs, rlVector2 rhs)
{
	return (lhs.getXf() * rhs.getXf()) + (lhs.getYf() * rhs.getYf());
}

rlVector2 & operator*(rlVector2 lhs, const float& rhs)
{
	lhs.setX(lhs.getXf() * rhs);
	lhs.setY(lhs.getYf() * rhs);
	return lhs;
}

rlVector2 & operator+(rlVector2 lhs, const float& rhs)
{
	lhs.setX(lhs.getXf() * rhs);
	lhs.setY(lhs.getYf() * rhs);
	return lhs;
}

float rlVector2::Distance(rlVector2& vec1, rlVector2& vec2)
{
	return 0.0f;
}
