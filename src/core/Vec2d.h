/*
 * Vec2d.h
 *
 *  Created on: 19/10/2010
 *      Author: pete
 */

#ifndef VEC2D_H_
#define VEC2D_H_

class Vec2d
{
public:
	Vec2d();
	Vec2d( double x, double y );
	virtual ~Vec2d();

	double x;
	double y;

	Vec2d operator+( const Vec2d& );
	void operator+=( const Vec2d& );
	Vec2d operator-( const Vec2d& );
	void operator-=( const Vec2d& );
	Vec2d operator*( const double& );
	Vec2d operator/( const double& );
	double mag();
	Vec2d unit();

};

#endif /* VEC2D_H_ */
