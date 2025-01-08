#pragma once
#include "raylib.h"
#include "mytexture2d.h"

struct Projectile
{
public:

	int speed = 15;
	bool active = true;
	Vector2 position = { 0,0 };
	Vector2 lineStart = { 0, 0 };
	Vector2 lineEnd = { 0, 0 };

	Projectile(Vector2 _position, int _speed)
	{
		position = _position;
		speed = _speed;
	}

	void Update();
	void Render(const MyTexture2D& texture);
};