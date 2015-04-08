#ifndef GAME_DUMB_ENEMY_SYSTEM_H
#define GAME_DUMB_ENEMY_SYSTEM_H

#include <ES/DisArray.h>
#include <Game/UpdatableSystem.h>
#include <Game/SimpleMovementManager.h>
#include <Game/Vector2f.h>
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

	class DumbEnemySystem : public UpdatableSystem
	{
		friend class DumbEnemyInstance;
		es::DisArray<float> _health;
		es::DisArray<Vector2f> _position;
		es::DisArray<Vector2f> _direction;

		typedef decltype(_health) healthArr;
		typedef decltype(_position) vectorArr;
	public:
		DumbEnemySystem(std::uint16_t size) : UpdatableSystem(size), _health(size), _position(size), _direction(size) { }

		void Tick(float deltaTime)
		{
			
//#define USE_THREADS
#ifdef USE_THREADS
			vectorArr p1, p2, p3;
			vectorArr d1, d2, d3;
			std::uint16_t size = _elementCount / 3;

			vectorArr::Slice(&p1, _position, size * 0, size);
			vectorArr::Slice(&p2, _position, size * 1, size);
			vectorArr::Slice(&p3, _position, size * 2, size);

			vectorArr::Slice(&d1, _direction, size * 0, size);
			vectorArr::Slice(&d2, _direction, size * 1, size);
			vectorArr::Slice(&d3, _direction, size * 2, size);
			
			std::thread t2(SimpleMovementManager::Process, &p1, &d1, size, deltaTime);
			std::thread t3(SimpleMovementManager::Process, &p2, &d2, size, deltaTime);
			std::thread t4(SimpleMovementManager::Process, &p3, &d3, size, deltaTime);
			std::thread t1([](healthArr *health, std::uint16_t count, float deltaTime)
			{
				float *healthIt = health->GetRaw();
				for (std::uint16_t i = 0; i < count; ++i, ++healthIt)
				{
					*healthIt -= deltaTime;
				}
			}, &_health, _elementCount, deltaTime);

			t2.join();
			t3.join();
			t4.join();
			t1.join();
#undef USE_THREADS
#else
			SimpleMovementManager::Process(&_position, &_direction, _elementCount, deltaTime);
			float *healthIt = _health.GetRaw();
			std::uint16_t count = _elementCount;
			for (std::uint16_t i = 0; i < count; ++i, ++healthIt)
			{
				*healthIt -= deltaTime;
			}
#endif
		}

		DumbEnemyInstance GetInstance(Reference reference)
		{
			return DumbEnemyInstance(this, this->GetHandle(reference));
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