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
	class Vector2f
	{
	public:
		float x;
		float y;

		/****************
		 * Construction *
		 ****************/

		Vector2f() { }
		Vector2f(float x, float y) : x(x), y(y) { }

		static Vector2f CreateZero()
		{
			return Vector2f(0, 0);
		}

		/**
		 * @brief Creates a unit vector pointing in the direction of a
		 *
		 * @param an Angle in radians
		 */
		static Vector2f FromAngle(float a)
		{
			Vector2f(::cos(a), ::sin(a));
		}

		/***********
		 * Methods *
		 ***********/

		/**
		 * @brief Returns the magnitude squared
		 */
		float GetLength2() const
		{
			return x * x + y * y;
		}

		/**
		 * @brief Returns the magnitude
		 */
		float GetLength() const
		{
			return ::sqrt(GetLength2());
		}

		/**
		 * @brief Normalizes the vector.
		 */
		Vector2f &Normalize()
		{
			float length = GetLength();
			x /= length;
			y /= length;
			return *this;
		}

		/**
		 * @brief Returns a unit vector pointing in the same direction as the current vector
		 */
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

		/**********************
		 * Vector2f operators *
		 **********************/

		/**
		 * @brief Cross product
		 */
		friend float operator%(const Vector2f &lhs, const Vector2f &rhs)
		{
			return Vector2f::Cross(lhs, rhs);
		}

		/**
		 * @brief Dot product
		 */
		friend float operator*(const Vector2f &lhs, const Vector2f &rhs)
		{
			return Vector2f::Dot(lhs, rhs);
		}

		friend Vector2f &operator+=(Vector2f &lhs, const Vector2f &rhs)
		{
			lhs.x += rhs.x;
			lhs.y += rhs.y;
			return lhs;
		}

		friend Vector2f &operator-=(Vector2f &lhs, const Vector2f &rhs)
		{
			lhs.x -= rhs.x;
			lhs.y -= rhs.y;
			return lhs;
		}

		friend Vector2f operator+ (Vector2f lhs, const Vector2f &rhs)
		{
			return lhs += rhs;
		}

		friend Vector2f operator- (Vector2f lhs, const Vector2f &rhs)
		{
			return lhs -= rhs;
		}

		friend Vector2f &operator*=(Vector2f &v, float scalar)
		{
			v.x *= scalar;
			v.y *= scalar;
			return v;
		}

		friend Vector2f operator*(Vector2f v, float scalar)
		{
			return v *= scalar;
		}

		friend Vector2f operator*(float scalar, const Vector2f &v)
		{
			return v * scalar;
		}

		friend Vector2f operator-(const Vector2f &v)
		{
			return Vector2f(-v.x, -v.y);
		}
	};
}

#endif
