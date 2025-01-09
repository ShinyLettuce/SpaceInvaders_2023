#pragma once
#include "raylib.h"
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
#include <chrono>

class Game
{
	float shootTimer = 0;
	float alienSpacing = 80;
	float formationX = 100;
	float formationY = 50;
	int formationWidth = 8;
	int formationHeight = 5;
	int wallCount = 5;
	int score = 0;
	bool gameOver = false;
	Rectangle rec = { 0, 0 ,0 ,0 };

	std::array<MyTexture2D, 3> shipTextures{ MyTexture2D{"./Assets/Ship1.png"}, MyTexture2D{"./Assets/Ship2.png"}, MyTexture2D{"./Assets/Ship3.png"} };
	MyTexture2D alienTexture{ "./Assets/Alien.png" };
	MyTexture2D barrierTexture{ "./Assets/Barrier.png" };
	MyTexture2D laserTexture{ "./Assets/Laser.png" };

	Player player;
	std::vector<Projectile> playerProjectiles;
	std::vector<Projectile> enemyProjectiles;
	std::vector<Wall> walls;
	std::vector<Alien> aliens;
	Background background;

	void end() noexcept;
	void spawnAliens();
	void spawnWalls();
	bool circleLineCollision(Vector2 circlePos, float circleRadius, Vector2 lineTop, Vector2 lineBottom) const noexcept;
	void createPlayerProjectile();
	void createEnemyProjectile();
	void removeDeadEntities();
	void checkCollisions();
public:

	void start();
	void update();
	void render();

	bool isGameOver() const noexcept { return gameOver; }
	int getScore() const noexcept{ return score; }
};