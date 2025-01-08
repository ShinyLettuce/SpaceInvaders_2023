#pragma once
#include "raylib.h"
#include <iostream>
#include "mytexture2d.h"

struct Player
{
public:
	Player()
	{
		float window_width = static_cast<float>(GetScreenWidth());
		x_pos = window_width / 2;
		std::cout << "Find Player -X:" << GetScreenWidth() / 2 << "Find Player -Y" << GetScreenHeight() - player_base_height << std::endl;
	}

	float x_pos = 0;
	float speed = 7;
	float player_base_height = 70.0f;
	float radius = 50;
	int lives = 3;
	int direction = 0;
	int activeTexture = 0;
	float timer = 0;

	void Render(const MyTexture2D& texture);
	void Update();

};