/*
 * Vec2d.cpp
 *
 *  Created on: 19/10/2010
 *      Author: pete
 */

#include "Vec2d.h"
#include <cmath>

Vec2d::Vec2d() : x( 0 ), y( 0 )
{
	this->x = 0;
	this->y = 0;
}

Vec2d::Vec2d( double x, double y ) : x( x ), y( y ) { }

Vec2d::~Vec2d() { }

Vec2d Vec2d::operator+( const Vec2d& value )
{
	Vec2d result;
	result.x = this->x + value.x;
	result.y = this->y + value.y;
	return result;
}

void Vec2d::operator+=( const Vec2d& value )
{
	this->x += value.x;
	this->y += value.y;
}

Vec2d Vec2d::operator-( const Vec2d& value )
{
	Vec2d result;
	result.x = this->x - value.x;
	result.y = this->y - value.y;
	return result;
}

void Vec2d::operator-=( const Vec2d& value )
{
	this->x -= value.x;
	this->y -= value.y;
}

Vec2d Vec2d::operator*( const double& value )
{
	Vec2d result;
	result.x *= value;
	result.y *= value;
	return result;
}

Vec2d Vec2d::operator/( const double& value )
{
	Vec2d result;
	result.x /= value;
	result.y /= value;
	return result;
}

double Vec2d::mag()
{
	return sqrt( this->x * this->x + this->y * this->y );
}

Vec2d Vec2d::unit()
{
	double magnitude = this->mag();
	Vec2d result;
	result.x = this->x / magnitude;
	result.y = this->y / magnitude;
	return result;
}
