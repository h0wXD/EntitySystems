#ifndef GAME_SIMPLE_MOVEMENT_MANAGER_H
#define GAME_SIMPLE_MOVEMENT_MANAGER_H

#include <ES/DisArray.h>
#include <Game/Vector2f.h>
#include <algorithm>
#include <iostream>
#include <ES/transform_self.h>

namespace game
{
	class SimpleMovementManager
	{
	public:
		static void Process(es::DisArray<Vector2f> *position, es::DisArray<Vector2f> *direction, std::int16_t count, float deltaTime)
		{
			es::transform_self(*position, *direction, [deltaTime](Vector2f &pos, Vector2f &dir)
			{
				pos.x += dir.x * deltaTime;
				pos.y += dir.y * deltaTime;
			});
		}
	};
}

#endif
