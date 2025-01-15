#pragma once
#include "raylib.h"
#include "mytexture2d.h"

struct Wall
{
public:
	Vector2 position = { 0,0 };
	Rectangle rec = { 0,0,0,0 };
	bool active = true;
	Color color = WHITE;
	int health = 50;
	float radius = 60;


	void Render(const MyTexture2D& texture) const noexcept;
	void Update() noexcept;
};