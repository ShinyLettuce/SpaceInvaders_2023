#pragma once
#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)
#include "mytexture2d.h"
#include "star.h"
#include "wall.h"
#include "alien.h"
#include "player.h"
#include "projectile.h"
#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <random>
#include "mathutils.h"
#include "constants.h"
#pragma warning(push)
#pragma warning(disable: 26446) //gsl::at() warning

class Game
{
	int shootTimer = 0;
	int score = 0;
	bool gameOver = false;
	Rectangle rec = { 0, 0 ,0 ,0 };

	std::array<MyTexture2D, 3> shipTextures{ 
		MyTexture2D{"./Assets/Ship1.png"},
		MyTexture2D{"./Assets/Ship2.png"},
		MyTexture2D{"./Assets/Ship3.png"} };
	MyTexture2D alienTexture{ "./Assets/Alien.png" };
	MyTexture2D barrierTexture{ "./Assets/Barrier.png" };
	MyTexture2D laserTexture{ "./Assets/Laser.png" };

	Background background = Background{ 600 };
	Projectile enemyProjectile{ Vector2i{ -99, -99}, 0 };
	std::vector<Projectile> playerProjectiles;
	std::vector<Alien> aliens;
	std::vector<Wall> walls;
	Player player;

	void end() noexcept;
	void spawnAliens();
	void spawnWalls();
	void createPlayerProjectile();
	void createEnemyProjectile() noexcept;
	void removeDeadEntities();
	bool checkForGameOver() const noexcept;
	void checkCollisions() noexcept;
public:

	void start();
	void update();
	void render() noexcept;

	bool isGameOver() const noexcept { return gameOver; }
	int getScore() const noexcept{ return score; }
};