#pragma once
#include "raylib.h"
#include "mytexture2d.h"
#include "star.h"
#include "wall.h"
#include "alien.h"
#include "player.h"
#include "projectile.h"
#include "entitytype.h"
#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <iostream>
#include <chrono>

enum struct State
{
	STARTSCREEN,
	GAMEPLAY,
	ENDSCREEN
};

struct Game
{
	State gameState = {};
	int score;

	// for later, make a file where you can adjust the number of walls (config file) 
	int wallCount = 5;

	//Aliens shooting
	float shootTimer = 0;

	//Aliens stuff? (idk cause liv wrote this)
	Rectangle rec = { 0, 0 ,0 ,0 }; 

	int formationWidth = 8;
	int formationHeight = 5;
	int alienSpacing = 80;
	int formationX = 100;
	int formationY = 50;
	bool gameOver = false;
	
	Game() {
		gameState = State::STARTSCREEN;
	}

	void Start();
	void End();
	void Update();
	void Render();
	void SpawnAliens();
	bool circleLineCollision(Vector2 circlePos, float circleRadius, Vector2 lineTop, Vector2 lineBottom);

	void createPlayerProjectile();
	void removeDeadEntities();
	void checkCollisions();

	// Entity Storage and Resources
	std::array<MyTexture2D, 3> shipTextures{ MyTexture2D{"./Assets/Ship1.png"}, MyTexture2D{"./Assets/Ship2.png"}, MyTexture2D{"./Assets/Ship3.png"} };
	MyTexture2D alienTexture{ "./Assets/Alien.png" };
	MyTexture2D barrierTexture{ "./Assets/Barrier.png" };
	MyTexture2D laserTexture{ "./Assets/Laser.png" };

	Player player;
	std::vector<Projectile> Projectiles;
	std::vector<Wall> Walls;
	std::vector<Alien> Aliens;
	Background background;

	Vector2 playerPos;
	Vector2 alienPos; 
	Vector2 cornerPos;
	float offset;
};