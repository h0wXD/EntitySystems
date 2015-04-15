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


#ifndef GAME_SIMPLE_BULLET_SYSTEM_H
#define GAME_SIMPLE_BULLET_SYSTEM_H

#include <ES/System.h>
#include <ES/disarray.h>
#include <ES/for_each_where.h>

#include <Game/ILogic.h>
#include <Game/Vector2.h>
#include <Game/SimpleMovementManager.h>

namespace game
{

	class SimpleBulletSystem;

	/**************************************
	 * Simple Bullet instance declaration *
	 **************************************/
	class SimpleBulletInstance
	{
		friend class SimpleBulletSystem;
		es::System::Handle _handle;
		SimpleBulletSystem *_system;

		SimpleBulletInstance(SimpleBulletSystem *system, es::System::Handle handle) : 
			_system(system), _handle(handle) { }
	public:
		inline Vector2f &Position();
		inline Vector2f &Direction();
	};

	/************************
	 * Simple Bullet system *
	 ************************/
	class SimpleBulletSystem : public es::System
	{
		friend class SimpleBulletInstance;
		es::disarray<Vector2f> _positionArray;
		es::disarray<Vector2f> _directionArray;

	public:
		SimpleBulletSystem(std::uint16_t size) : 
			_positionArray(size), 
			_directionArray(size), 
			System() { }

		es::System::Handle Add()
		{
			Handle handle = CreateHandle();
			IncreaseElementCount();
			return handle;
		}

		void Tick(float deltaTime)
		{
			std::uint16_t toRemove[255];
			SimpleMovementManager::Process(&_positionArray, &_directionArray, _elementCount, deltaTime);

			auto OutOfBounds = [](const Vector2f &pos)
			{
				float x = ::abs(pos.x);
				float y = ::abs(pos.y);

				return x > 2 || y > 2;
			};
			int count = 0;
			auto AddToRemove = [&count, &toRemove](int i)
			{
				toRemove[count] = i;
				count++;
			};
			es::for_where_n(_positionArray.begin(), _elementCount, OutOfBounds, AddToRemove);
			while (count > 0)
			{
				--count;
				System::Remove(toRemove[count], count, _positionArray, _directionArray);
			}
		}

		SimpleBulletInstance GetInstance(Handle handle)
		{
			return SimpleBulletInstance(this, handle);
		}
	};

	/*************************************
	 * Simple Bullet instance definition *
	 *************************************/
	Vector2f &SimpleBulletInstance::Position()
	{
		return _system->_positionArray[_handle.GetId()];
	}

	Vector2f &SimpleBulletInstance::Direction()
	{
		return _system->_directionArray[_handle.GetId()];
	}
}

#endif
