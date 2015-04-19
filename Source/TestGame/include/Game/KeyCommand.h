#ifndef GAME_KEY_COMMAND_H
#define GAME_KEY_COMMAND_H

#include <GLFW/glfw3.h>

namespace game
{

	struct KeyCommand
	{
		GLFWwindow *Window;
		int Key;
		int Scancode;
		int Modifiers;

		KeyCommand(const KeyCommand &command) :
			Window(command.Window),
			Key(command.Key),
			Scancode(command.Scancode),
			Modifiers(command.Modifiers) { }

		KeyCommand() { }

		KeyCommand(GLFWwindow *window, int key, int scancode, int modifiers) :
			Window(window),
			Key(key),
			Scancode(scancode),
			Modifiers(modifiers) { }

	};
}

#endif