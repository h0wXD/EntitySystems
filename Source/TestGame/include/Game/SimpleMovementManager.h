#ifndef GAME_SIMPLE_MOVEMENT_MANAGER_H
#define GAME_SIMPLE_MOVEMENT_MANAGER_H

#include <ES/DisArray.h>
#include <Game/Vector2f.h>
#include <algorithm>
#include <iostream>

namespace game
{
	class SimpleMovementManager
	{
	public:
		static void Process(es::DisArray<Vector2f> *position, es::DisArray<Vector2f> *direction, std::int16_t count, float deltaTime)
		{
			/*std::transform(position.begin(), position.begin() + count, direction.begin(), position.begin(), [&deltaTime](const Vector2f &v1, const Vector2f &v2)
			{
				return v1 + v2 * deltaTime;
			});*/
			Vector2f *v1 = position->GetRaw();
			Vector2f *v2 = direction->GetRaw();
			for (std::uint16_t i = 0; i < count; ++i, ++v1, ++v2)
			{
				v1->x += v2->x * deltaTime;
				v1->y += v2->y * deltaTime;
			}
		}
	};
}

#endif
