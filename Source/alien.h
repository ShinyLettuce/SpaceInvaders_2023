#pragma once
#include "raylib.h"
#include "mytexture2d.h"

struct Alien
{
public:

	Color color = WHITE;
	Vector2 position = { 0, 0 };
	float speed = 2;
	float radius = 30;
	bool active = true;
	bool moveRight = true;

	Alien(Vector2 _pos)
		: position{ _pos }
	{}

	void Update() noexcept;
	void Render(const MyTexture2D& texture) const noexcept;
};