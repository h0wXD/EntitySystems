#ifndef GAME_DUMB_ENEMY_SYSTEM_H
#define GAME_DUMB_ENEMY_SYSTEM_H

#include <ES/DisArray.h>
#include <Game/UpdatableSystem.h>
#include <Game/SimpleMovementManager.h>
#include <Game/Vector2f.h>

namespace game
{
	class DumbEnemySystem : public UpdatableSystem
	{
		es::DisArray<float> _health;
		es::DisArray<Vector2f> _position;
		es::DisArray<Vector2f> _direction;
	public:
		void Tick(float deltaTime)
		{
			SimpleMovementManager::Process(_position, _direction, _elementCount);
		}
	};
}
#endif