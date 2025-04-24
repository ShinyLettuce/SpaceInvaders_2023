#pragma once
#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)
#include "mytexture2d.h"
#include "mathutils.h"
#include "constants.h"

struct Wall
{
public:
	Vector2i position = { 0,0 };
	bool active = true;
	int health = 50;

	explicit Wall(Vector2i _pos) noexcept :
		position{ _pos }
	{}

	void Render(const MyTexture2D& texture) const noexcept;
	void Update() noexcept;
};