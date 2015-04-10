/********************************************************************************
 *                                                                              *
 *  ╔═════════════╗                                                             *
 *  ║EntitySystems║                                                             *
 *  ╚═════════════╝                                                             *
 *━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*
                                                                                
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

#ifndef GAME_DUMB_ENEMY_SYSTEM_H
#define GAME_DUMB_ENEMY_SYSTEM_H

#include <ES/disarray.h>
#include <ES/ReferribleSystem.h>
#include <Game/SimpleMovementManager.h>
#include <Game/Vector2f.h>
#include <Game/ILogic.h>
#include <iostream>

#include <thread>
#include <future>

namespace game
{

	class DumbEnemyInstance
	{
		friend class DumbEnemySystem;
		DumbEnemySystem *_system;
		es::System::Handle _handle;

		DumbEnemyInstance(DumbEnemySystem *system, es::System::Handle handle) : _system(system), _handle(handle) { }
	public:
		float &Health();
		Vector2f &Position();
		Vector2f &Direction();
	};

	class DumbEnemySystem : public es::ReferribleSystem, public ILogic
	{
		friend class DumbEnemyInstance;
		es::disarray<float> _health;
		es::disarray<Vector2f> _position;
		es::disarray<Vector2f> _direction;

		typedef decltype(_health) healthArr;
		typedef decltype(_position) vectorArr;
	public:
		DumbEnemySystem(std::uint16_t size) : es::ReferribleSystem(size), _health(size), _position(size), _direction(size) { }

		void Remove(Handle handle)
		{
			ReferribleSystem::Remove(GetReference(handle));
			System::Remove(GetHandleId(handle), _elementCount, _health, _position, _direction);
		}

		void Tick(float deltaTime) override
		{
			
// #define USE_THREADS
#ifdef USE_THREADS
			std::thread t1(SimpleMovementManager::Process, &_position, &_direction, _elementCount, deltaTime);
			std::thread t2([](healthArr *health, std::uint16_t count, float deltaTime)
			{
				float *healthIt = health->GetRaw();
				for (std::uint16_t i = 0; i < count; ++i, ++healthIt)
				{
					*healthIt -= deltaTime;
				}
			}, &_health, _elementCount, deltaTime);

			t1.join();
			t2.join();
			
#undef USE_THREADS
#else
			SimpleMovementManager::Process(&_position, &_direction, _elementCount, deltaTime);
			float *healthIt = _health.GetRaw();
			std::uint16_t count = _elementCount;
			for (std::uint16_t i = 0; i < count; ++i, ++healthIt)
			{
				*healthIt -= deltaTime;
			}

			healthIt = _health.GetRaw();
			for (std::uint16_t i = 0; i < count; ++i, ++healthIt)
			{
				if (*healthIt <= 0)
				{
					Remove(CreateHandle(i));
				}
			}
#endif
		}

		DumbEnemyInstance GetInstance(Handle handle)
		{
			return DumbEnemyInstance(this, handle);
		}

		DumbEnemyInstance GetInstance(Reference reference)
		{
			return GetInstance(GetHandle(reference));
		}
	};

	float &DumbEnemyInstance::Health()
	{
		return _system->_health[_handle.GetId()];
	}

	Vector2f &DumbEnemyInstance::Position()
	{
		return _system->_position[_handle.GetId()];
	}

	Vector2f &DumbEnemyInstance::Direction()
	{
		return _system->_direction[_handle.GetId()];
	}
}
#endif