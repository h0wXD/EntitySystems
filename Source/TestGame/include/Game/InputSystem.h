#ifndef GAME_INPUT_SYSTEM_H
#define GAME_INPUT_SYSTEM_H

#include "KeyCommand.h"

#include <queue>

namespace game
{

	class InputSystem
	{
		std::queue<KeyCommand> _repeatQueue;
		std::queue<KeyCommand> _releaseQueue;
		std::queue<KeyCommand> _pressQueue;
	public:
		inline void AddPressed(const KeyCommand &command);
		inline void AddReleased(const KeyCommand &command);
		inline void AddRepeated(const KeyCommand &command);

		inline void HandleCommands();
	};

	void InputSystem::AddPressed(const KeyCommand &command)
	{
		_pressQueue.emplace(command);
	}

	void InputSystem::AddReleased(const KeyCommand &command)
	{
		_releaseQueue.emplace(command);
	}

	void InputSystem::AddRepeated(const KeyCommand &command)
	{
		_pressQueue.emplace(command);
	}

	void InputSystem::HandleCommands()
	{
		while (_repeatQueue.size() > 0)
		{
			KeyCommand command = _repeatQueue.back();
			// Handle command
			_repeatQueue.pop();
		}

		while (_releaseQueue.size() > 0)
		{
			KeyCommand command = _releaseQueue.back();
			_repeatQueue.pop();
		}

		while (_pressQueue.size() > 0)
		{
			KeyCommand command = _pressQueue.back();
			_pressQueue.pop();
		}

	}
}

#endif
