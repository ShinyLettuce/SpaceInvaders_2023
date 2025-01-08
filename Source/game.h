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
#include <iostream>
#include <chrono>

class Game
{
	int formationWidth = 8;
	int formationHeight = 5;
	int alienSpacing = 80;
	int formationX = 100;
	int formationY = 50;
	int wallCount = 5;
	float shootTimer = 0;
	Rectangle rec = { 0, 0 ,0 ,0 }; 
public:
	int score;
	bool gameOver = false;

	void Start();
	void End();
	void Update();
	void Render();
	void SpawnAliens();
	bool circleLineCollision(Vector2 circlePos, float circleRadius, Vector2 lineTop, Vector2 lineBottom);

	void createPlayerProjectile();
	void createEnemyProjectile();
	void removeDeadEntities();
	void checkCollisions();

	// Entity Storage and Resources
	std::array<MyTexture2D, 3> shipTextures{ MyTexture2D{"./Assets/Ship1.png"}, MyTexture2D{"./Assets/Ship2.png"}, MyTexture2D{"./Assets/Ship3.png"} };
	MyTexture2D alienTexture{ "./Assets/Alien.png" };
	MyTexture2D barrierTexture{ "./Assets/Barrier.png" };
	MyTexture2D laserTexture{ "./Assets/Laser.png" };

	Player player;
	std::vector<Projectile> playerProjectiles;
	std::vector<Projectile> enemyProjectiles;
	std::vector<Wall> Walls;
	std::vector<Alien> Aliens;
	Background background;

	Vector2 playerPos = { 0, 0 };
	Vector2 alienPos = { 0, 0 };
	Vector2 cornerPos = { 0, 0 };
	float offset;
};