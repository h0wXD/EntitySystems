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


#ifndef GAME_DUMB_ENEMY_SYSTEM_H
#define GAME_DUMB_ENEMY_SYSTEM_H

#include <ES/disarray.h>
#include <ES/ReferribleSystem.h>
#include <ES/for_each_where.h>
#include <Game/SimpleMovementManager.h>
#include <Game/Vector2.h>
#include <Game/ILogic.h>

namespace game
{

	/***********************************
	 * Dumb Enemy instance declaration *
	 ***********************************/

	/**
	 * @brief OO-like class to handle Dumb enemies
	 */
	class DumbEnemySystem;
	
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

	/*********************
	 * Dumb Enemy system *
	 *********************/
	class DumbEnemySystem : public es::ReferribleSystem, public ILogic
	{
		friend class DumbEnemyInstance;
		es::disarray<float> _health;
		es::disarray<Vector2f> _position;
		es::disarray<Vector2f> _direction;

		typedef decltype(_health) healthArr;
		typedef decltype(_position) vectorArr;
	public:
		explicit DumbEnemySystem(std::uint16_t size) : es::ReferribleSystem(size), _health(size), _position(size), _direction(size) { }

		void Remove(Handle handle)
		{
			ReferribleSystem::Remove(GetReference(handle));
			System::Remove(GetHandleId(handle), _elementCount, _health, _position, _direction);
		}

		void Tick(float deltaTime) override
		{
			int toRemove[255];
			int count = 0;
			
			SimpleMovementManager::Process(&_position, &_direction, _elementCount, deltaTime);
			auto HealthLessEqZero = [](const float h)
			{
				return h <= 0.f;
			};
			auto AddToRemove = [&count, &toRemove](int i)
			{
				toRemove[count++] = i;
			};

			es::for_where_n(_health.begin(), _elementCount, HealthLessEqZero, AddToRemove);
			while (--count >= 0)
			{
				Remove(GetHandle(CreateReference(toRemove[count])));
			}
		}

		/**
		 * @brief Get a DumbEnemyInstance by Handle
		 */
		DumbEnemyInstance GetInstance(Handle handle)
		{
			return DumbEnemyInstance(this, handle);
		}

		/**
		 * @brief Get a DumbEnemyInstance by Reference
		 */
		DumbEnemyInstance GetInstance(Reference reference)
		{
			return GetInstance(GetHandle(reference));
		}
	};

	/**************************************
	 * Dumb enemy instance implementation *
	 **************************************/
	inline float &DumbEnemyInstance::Health()
	{
		return _system->_health[_handle.GetId()];
	}

	inline Vector2f &DumbEnemyInstance::Position()
	{
		return _system->_position[_handle.GetId()];
	}

	inline Vector2f &DumbEnemyInstance::Direction()
	{
		return _system->_direction[_handle.GetId()];
	}
}
#endif