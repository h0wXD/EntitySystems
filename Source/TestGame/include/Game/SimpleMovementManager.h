#ifndef GAME_SIMPLE_MOVEMENT_MANAGER_H
#define GAME_SIMPLE_MOVEMENT_MANAGER_H

#include <ES/DisArray.h>
#include <Game/Vector2f.h>
#include <algorithm>

namespace game
{
	class SimpleMovementManager
	{
	public:
		static void Process(es::DisArray<Vector2f> &position, es::DisArray<Vector2f> &direction, std::int16_t count)
		{
			std::transform(position.begin(), position.begin() + count, direction.begin(), position.begin(), [](Vector2f &v1, Vector2f &v2)
			{
				v1 += v2;
			});
		}
	};
}
#endif
