/********************************************************************************
 │ 
 │  ╔═════════════╗
 │  ║EntitySystems║
 │  ╚═════════════╝
 ╰╼━━━━━━━━━━━━━━━━━━━━━━━╾
                                                                                
   Copyright (c) 2015 h0wXD & LorenzJ.                                          
   https://github.com/h0wXD                                                     
   https://github.com/LorenzJ                                                   
                                                                                
   Permission is hereby granted, free of charge, to any person obtaining a copy 
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights 
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell    
   copies of the Software, and to permit persons to whom the Software is        
   furnished to do so, subject to the following conditions:                     
                                                                                
   The above copyright notice and this permission notice shall be included in   
   all copies or substantial portions of the Software.                          
                                                                                
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR   
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,     
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE  
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER       
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN    
   THE SOFTWARE.                                                                
 ********************************************************************************/


#ifndef GAME_VECTOR2F_H
#define GAME_VECTOR2F_H

#include <cmath>

namespace game
{
	template <class T>
	class Vector2
	{
	public:
		T x;
		T y;

		/****************
		 * Construction *
		 ****************/

		Vector2() { }
		Vector2(T x, T y) : x(x), y(y) { }

		static Vector2 CreateZero()
		{
			return Vector2(0, 0);
		}

		/**
		 * @brief Creates a unit vector pointing in the direction of a
		 *
		 * @param an Angle in radians
		 */
		static Vector2 FromAngle(T a)
		{
			return Vector2(::cos(a), ::sin(a));
		}

		/***********
		 * Methods *
		 ***********/

		/**
		 * @brief Returns the magnitude squared
		 */
		T GetLength2() const
		{
			return x * x + y * y;
		}

		/**
		 * @brief Returns the magnitude
		 */
		T GetLength() const
		{
			return ::sqrt(GetLength2());
		}

		/**
		 * @brief Normalizes the vector.
		 */
		Vector2 &Normalize()
		{
			auto length = GetLength();
			x /= length;
			y /= length;
			return *this;
		}

		/**
		 * @brief Returns a unit vector pointing in the same direction as the current vector
		 */
		Vector2 Normalized() const
		{
			auto v(*this);
			return v.Normalize();
		}

		static T Cross(const Vector2 &lhs, const Vector2 &rhs)
		{
			return lhs.x * rhs.y - lhs.y * rhs.x;
		}

		static T Dot(const Vector2 &lhs, const Vector2 &rhs)
		{
			return lhs.x * rhs.x + lhs.y * rhs.y;
		}

		/**********************
		 * Vector2 operators *
		 **********************/

		/**
		 * @brief Cross product
		 */
		friend T operator%(const Vector2 &lhs, const Vector2 &rhs)
		{
			return Vector2::Cross(lhs, rhs);
		}

		/**
		 * @brief Dot product
		 */
		friend T operator*(const Vector2 &lhs, const Vector2 &rhs)
		{
			return Vector2::Dot(lhs, rhs);
		}

		friend Vector2 &operator+=(Vector2 &lhs, const Vector2 &rhs)
		{
			lhs.x += rhs.x;
			lhs.y += rhs.y;
			return lhs;
		}

		friend Vector2 &operator-=(Vector2 &lhs, const Vector2 &rhs)
		{
			lhs.x -= rhs.x;
			lhs.y -= rhs.y;
			return lhs;
		}

		friend Vector2 operator+ (Vector2 lhs, const Vector2 &rhs)
		{
			return lhs += rhs;
		}

		friend Vector2 operator- (Vector2 lhs, const Vector2 &rhs)
		{
			return lhs -= rhs;
		}

		friend Vector2 &operator*=(Vector2 &v, T scalar)
		{
			v.x *= scalar;
			v.y *= scalar;
			return v;
		}

		friend Vector2 operator*(Vector2 v, T scalar)
		{
			return v *= scalar;
		}

		friend Vector2 operator*(T scalar, const Vector2 &v)
		{
			return v * scalar;
		}

		friend Vector2 operator-(const Vector2 &v)
		{
			return Vector2(-v.x, -v.y);
		}
	};

	typedef Vector2<float> Vector2f;
	typedef Vector2<double> Vector2d;
}

#endif
