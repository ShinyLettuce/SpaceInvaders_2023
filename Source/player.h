#pragma once
#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)
#include <iostream>
#include "mytexture2d.h"
#include "mathutils.h"
#include "constants.h"

struct Player
{
public:
	Player() noexcept
	{
		const auto window_width = GetScreenWidth();
		x_pos = window_width / 2;
	}

	int x_pos = 0;
	int player_base_height = 70;
	float direction = 0;
	float timer = 0;
	int lives = 3;
	int activeTexture = 0;

	void Render(const MyTexture2D& texture) const noexcept;
	void Update() noexcept;
};