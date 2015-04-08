#ifndef GAME_UPDATABLE_SYSTEM_H
#define GAME_UPDATABLE_SYSTEM_H

#include <ES/System.h>

namespace game
{
	class UpdatableSystem : public es::System
	{
	public:
		UpdatableSystem(std::uint16_t size) : es::System(size) { }
		virtual void Tick(float deltaTime) = 0;

	};
}

#endif
