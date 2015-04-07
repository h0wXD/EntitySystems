#include <ES/System.h>
#include <Game/Vector2f.h>

#include <iostream>

int main(int argc, char *argv[])
{
	using game::Vector2f;

	Vector2f vector{ 5, 2 };
	vector += Vector2f{ 10, 8 };
	std::cout << vector.x << "; " << vector.y;
	std::cin.peek();
}