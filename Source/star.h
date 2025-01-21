#pragma once
#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)
#include <vector>

struct Star
{
	Vector2 initPosition = { 0, 0 };
	Vector2 position = { 0, 0 };
	Color color = SKYBLUE;
	float size = 0;

	Star() noexcept
	{
		initPosition.x = static_cast<float>(GetRandomValue(-150, GetScreenWidth() + 150));
		initPosition.y = static_cast<float>(GetRandomValue(0, GetScreenHeight()));
		size = static_cast<float>(GetRandomValue(1, 4) / 2);
	}

	void Update(float starOffset) noexcept;
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

	void Update(float offset) noexcept;
	void Render() const noexcept;
};