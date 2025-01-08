#pragma once
#include "raylib.h"
#include <vector>

struct Star
{
	Vector2 initPosition = { 0, 0 };
	Vector2 position = { 0, 0 };
	Color color = SKYBLUE;
	float size = 0;

	Star()
	{
		initPosition.x = GetRandomValue(-150, GetScreenWidth() + 150);
		initPosition.y = GetRandomValue(0, GetScreenHeight());
		size = GetRandomValue(1, 4) / 2;
	}

	void Update(float starOffset);
	void Render();
};

struct Background
{
	std::vector<Star> Stars;

	void Initialize(int starAmount);
	void Update(float offset);
	void Render();

};