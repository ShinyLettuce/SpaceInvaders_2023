#pragma once
#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)
#include <vector>
#include "mathutils.h"
#include "constants.h"

struct Star
{
	Vector2i initPosition = { 0, 0 };
	Vector2i position = { 0, 0 };
	int size = 0;

	Star() noexcept
	{
		initPosition.x = GetRandomValue(-150, GetScreenWidth() + 150);
		initPosition.y = GetRandomValue(0, GetScreenHeight());
		size = GetRandomValue(1, 4) / 2;
	}

	void Update(int starOffset) noexcept;
	void Render() const noexcept;
};

struct Background
{
	std::vector<Star> Stars;

	explicit Background(int starAmount)
	{
		for (int i = 0; i < starAmount; i++)
		{
			const Star newStar;
			Stars.push_back(newStar);
		}
	}

	void Update(int offset) noexcept;
	void Render() const noexcept;
};