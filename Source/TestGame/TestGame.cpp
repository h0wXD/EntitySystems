#include <ES/System.h>
#include <Game/Vector2f.h>
#include <Game/DumbEnemySystem.h>
#include <iostream>
#include <chrono>

class Enemy
{
public:
	game::Vector2f position;
	virtual void Update(float deltaTime) = 0;
};

class DumbEnemy : public Enemy
{
public:
	game::Vector2f direction;
	float health;
	void Update(float deltaTime) override
	{
		position.x += direction.x;
		position.y += direction.y;
		health -= deltaTime;
	}
};

int main(int argc, char *argv[])
{
	using game::Vector2f;
	using game::DumbEnemySystem;
	using game::DumbEnemyInstance;
	using es::System;

	DumbEnemySystem system(30000);
	for (unsigned i = 0; i < 30000; ++i)
	{
		System::Reference enemyReference = system.Add();
		DumbEnemyInstance instance = system.GetInstance(enemyReference);

		instance.Health() = 5;
		instance.Direction() = Vector2f{ 0.5f, 2.f };
		instance.Position() = Vector2f{ 0, 0 };

		if (!(i % 1000))
		{
			std::cout << i << std::endl;
		}
	}

	Enemy **enemies = new Enemy*[30000];
	for (std::size_t i = 0; i < 30000; ++i)
	{
		DumbEnemy *dumbEnemy = new DumbEnemy();
		dumbEnemy->position = Vector2f{ 0, 0 };
		dumbEnemy->direction = Vector2f{ 0.5f, 2.f };
		dumbEnemy->health = 5;

		enemies[i] = dumbEnemy;
	}


	std::cout << "Starting benchmark" << std::endl;
	std::cout << "Data oriented" << std::endl;
	{
		std::chrono::high_resolution_clock clock;
		std::chrono::high_resolution_clock::time_point start = clock.now();
		for (unsigned i = 0; i < 50000; ++i)
		{
			system.Tick(0.16f);
			if (!(i % 10000))
			{
				std::cout << i << "/" << 50000 << std::endl;
			}
		}
		std::chrono::high_resolution_clock::time_point end = clock.now();
		std::chrono::duration<double> elapsed = end - start;
		std::cout << elapsed.count() << 's' << std::endl;
	}
	std::cout << "Naive OO" << std::endl;
	{
		std::chrono::high_resolution_clock clock;
		std::chrono::high_resolution_clock::time_point start = clock.now();
		for (unsigned i = 0; i < 50000; ++i)
		{
			for (std::size_t t = 0; t < 30000; ++t)
			{
				enemies[t]->Update(0.16f);
			}
			if (!(i % 10000))
			{
				std::cout << i << "/" << 50000 << std::endl;
			}
		}
		std::chrono::high_resolution_clock::time_point end = clock.now();
		std::chrono::duration<double> elapsed = end - start;
		std::cout << elapsed.count() << 's' << std::endl;
	}
	std::cin.peek();
}

