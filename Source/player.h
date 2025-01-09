#pragma once
#include "raylib.h"
#include <iostream>
#include "mytexture2d.h"

struct Player
{
public:
	Player() noexcept
	{
		const auto window_width = static_cast<float>(GetScreenWidth());
		x_pos = window_width / 2;
	}

	float timer = 0;
	float x_pos = 0;
	float speed = 7;
	float radius = 50;
	float direction = 0;
	float player_base_height = 70.0f;
	int lives = 3;
	int activeTexture = 0;

	void Render(const MyTexture2D& texture) const noexcept;
	void Update() noexcept;
};