#pragma once
#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)
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

	explicit Wall(Vector2 _pos) noexcept :
		position{ _pos }
	{
	}

	void Render(const MyTexture2D& texture) const noexcept;
	void Update() noexcept;
};