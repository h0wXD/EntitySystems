#ifndef GAME_VECTOR2F_H
#define GAME_VECTOR2F_H

#include <cmath>

namespace game
{
	class Vector2f
	{
	public:
		float x;
		float y;

		Vector2f() { }
		Vector2f(float x, float y) : x(x), y(y) { }

		float GetLength2() const
		{
			return x * x + y * y;
		}

		float GetLength() const
		{
			return ::sqrt(GetLength2());
		}

		Vector2f &Normalize()
		{
			float length = GetLength();
			x /= length;
			y /= length;
			return *this;
		}

		Vector2f Normalized() const
		{
			auto v(*this);
			return v.Normalize();
		}

		static float Cross(const Vector2f &lhs, const Vector2f &rhs)
		{
			return lhs.x * rhs.y - lhs.y * rhs.x;
		}

		static float Dot(const Vector2f &lhs, const Vector2f &rhs)
		{
			return lhs.x * rhs.x + lhs.y * rhs.y;
		}
	};

	inline Vector2f &operator+=(Vector2f &lhs, const Vector2f &rhs)
	{
		lhs.x += rhs.x;
		lhs.y += rhs.y;
		return lhs;
	}

	inline Vector2f operator+ (const Vector2f &lhs, const Vector2f rhs)
	{
		auto v(lhs);
		v += rhs;
		return v;
	}

	inline Vector2f operator-=(Vector2f &lhs, const Vector2f &rhs)
	{
		lhs.x -= rhs.x;
		lhs.y -= rhs.y;
		return lhs;
	}

	inline Vector2f operator- (const Vector2f &lhs, const Vector2f &rhs)
	{
		auto v(lhs);
		v -= rhs;
		return v;
	}

	inline Vector2f &operator*=(Vector2f &v, float scalar)
	{
		v.x *= scalar;
		v.y *= scalar;
		return v;
	}

	inline Vector2f operator*(const Vector2f &v, float scalar)
	{
		auto v2(v);
		return v2 *= scalar;
	}

	inline Vector2f operator*(float scalar, const Vector2f &v)
	{
		return v * scalar;
	}

	inline Vector2f &operator+=(Vector2f &lhs, Vector2f &&rhs)
	{
		lhs.x += rhs.x;
		lhs.y += rhs.y;
		return lhs;
	}

	inline Vector2f &operator-=(Vector2f &lhs, Vector2f &&rhs)
	{
		lhs.x -= rhs.x;
		lhs.y -= rhs.y;
		return lhs;
	}

	
}

#endif
