/*
 * ARVector2.h
 *
 *  Created on: Mar 21, 2017
 *      Author: Kamil
 */

#ifndef ARVECTOR2_H_
#define ARVECTOR2_H_

#include "ARMath.h"
#include "ARUtils.h"

namespace AutoRobo
{
	class Vector2
	{
	public:
		// Max error in sq_distance between vectors to be considered equal
		static constexpr float equalityErrorSquared = 1e-3;

	private:
		float _x;
		float _y;

	public:
		constexpr Vector2() :
				_x((float)0), _y((float)0)
		{
		}

		constexpr Vector2(float x, float y) :
				_x(x), _y(y)
		{
		}

		constexpr float x() const
		{
			return _x;
		}
		constexpr float& x()
		{
			return _x;
		}
		constexpr float y() const
		{
			return _y;
		}
		constexpr float& y()
		{
			return _y;
		}

		constexpr bool operator==(const Vector2& v) const
		{
			return distanceToSquared(v) < equalityErrorSquared;
		}

		constexpr bool operator!=(const Vector2& v) const
		{
			return !(*this == v);
		}

		// Returns Vector2 : point-wise added 2 Vector2 'a' and 'b'
		constexpr Vector2 operator+(const Vector2& v) const
		{
			return Vector2(x() + v.x(), y() + v.y());
		}

		// Returns Vector2 : point-wise subtracted 2 Vector2 'a' and 'b'
		constexpr Vector2 operator-(const Vector2& v) const
		{
			return Vector2(x() - v.x(), y() - v.y());
		}

		// Returns Vector2 : point-wise multiplied 2 Vector2 'a' and 'b'
		constexpr Vector2 operator*(const Vector2& v) const
		{
			return Vector2(x() * v.x(), y() * v.y());
		}

		// Returns Vector2 : point-wise divided 2 Vector2 'a' and 'b'
		constexpr Vector2 operator/(const Vector2& v) const
		{
			return Vector2(x() * v.x(), y() * v.y());
		}

		constexpr float sum() const
		{
			return x() + y();
		}

		constexpr float dot(const Vector2& v) const
		{
			return x() * v.x() + y() * v.y();
		}

		constexpr float cross(const Vector2& v) const
		{
			return x() * v.y() - y() * v.x();
		}

		constexpr float lengthSquared() const
		{
			return dot(*this);
		}

		float length() const
		{
			return (float)sqrtf(lengthSquared());
		}

		constexpr float distanceToSquared(const Vector2& v) const
		{
			return (*this - v).lengthSquared();
		}

		float distanceTo(const Vector2& v) const
		{
			return (float)sqrtf(distanceToSquared(v));
		}

		void addToThis(const Vector2& v)
		{
			x() = x() + v.x();
			y() = y() + v.y();
		}

		void subFomThis(const Vector2& v)
		{
			x() = x() - v.x();
			y() = y() - v.y();
		}

		void subFomThisRight(const Vector2& v)
		{
			x() = v.x() - x();
			y() = v.y() - y();
		}

		void multThis(const Vector2& v)
		{
			x() = x() * v.x();
			y() = y() * v.y();
		}

		void divThis(const Vector2& v)
		{
			x() = x() / v.x();
			y() = y() / v.y();
		}

		void divThisRight(const Vector2& v)
		{
			x() = v.x() / x();
			y() = v.y() / y();
		}

		// Creates direction vector. Angle is counted from OY in left-hand frame
		static constexpr Vector2 FromAngle_YX(float angle)
		{
			return Vector2 { -(float)sin(angle), (float)cos(angle) };
		}

		// Creates direction vector. Angle is counted from OX in left-hand frame
		static constexpr Vector2 FromAngle_XY(float angle)
		{
			return Vector2 { (float)cos(angle), (float)sin(angle) };
		}

		void normalize()
		{
			float l = 1 / length();
			x() = x() * l;
			y() = y() * l;
		}

		Vector2 normalized() const
		{
			float l = 1 / length();
			return Vector2 { x() * l, y() * l };
		}

		void rotate(float angle)
		{
			//vec = r*[cos(a),sin(a),z] : r is norm, a is angle of vec from X axis
			// vec_rotated = r*[cos(a)cos(da) - sin(a)*sin(da), sin(a)cos(da) + cos(a)sin(da),z]
			// vec_rotated = [vec.x*cos(da) - vec.y*sin(da), vec.y*cos(da) + vec.x*sin(da),z]
			// If angle is counted from Y axis then vec = r*[-sin(a),cos(a),z]
			// but final formula stays the same
			float cosda = (float)cos(angle);
			float sinda = (float)sin(angle);
			x() = x() * cosda - y() * sinda;
			y() = y() * cosda + x() * sinda;
		}

		Vector2 rotated(float angle) const
		{
			float cosda = (float)cos(angle);
			float sinda = (float)sin(angle);
			return Vector2 { x() * cosda - y() * sinda, y() * cosda
					+ x() * sinda };
		}

		// Returns angle in radian between 2 vectors in range (-pi,pi)
		float angleTo(const Vector2& v) const
		{
			// Angle is simple acos(v1*v2/|v1||v2|), but it is in (0,pi)
			// To determine angle sign we need:
			// dot(v1,v2) = |v1||v2|cosa, cross(v1,v2) = |v1||v2|sina,
			// tana = sina/cosa = cross/dot
			// ang = atan2(cross, dot)
			return atan2f(cross(v), dot(v));
		}

		// Returns vector rotated by 90
		constexpr Vector2 perpendicular() const
		{
			return Vector2(-y(), x());
		}

		// Returns vector rotated by -90
		constexpr Vector2 perpendicularReversed() const
		{
			return Vector2(y(), -x());
		}

		static const Vector2 Zero;
		static const Vector2 UnitX;
		static const Vector2 UnitY;
		static const Vector2 NegUnitX;
		static const Vector2 NegUnitY;
		static const Vector2 One;
	};
}

#endif /* ARVECTOR2_H_ */
