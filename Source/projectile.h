#pragma once
#include "raylib.h"
#include "entitytype.h"
#include "mytexture2d.h"

struct Projectile
{
public:
	Vector2 position = { 0,0 };
	int speed = 15;
	bool active = true;
	EntityType type = {};

	Vector2 lineStart = { 0, 0 };
	Vector2 lineEnd = { 0, 0 };

	void Update();

	void Render(const MyTexture2D& texture);
};