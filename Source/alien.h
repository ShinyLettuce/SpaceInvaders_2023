#pragma once
#include "raylib.h"
#include "entitytype.h"
#include "Resources.h"

struct Alien
{
public:

	Color color = WHITE;
	Vector2 position = { 0, 0 };
	int x = 0;
	int y = 0;
	float radius = 30;
	bool active = true;
	bool moveRight = true;

	EntityType type = EntityType::ENEMY;

	int speed = 2;

	void Update();
	void Render(const MyTexture2D& texture);
};