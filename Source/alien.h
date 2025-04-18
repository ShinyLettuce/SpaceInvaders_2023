#pragma once
#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)
#include "mytexture2d.h"
#include "mathutils.h"

struct Alien
{
public:
	Vector2i position = { 0, 0 };
	Box boundingBox = { 85, 30 };
	int speed = 2;
	bool active = true;
	bool moveRight = true;

	explicit Alien(Vector2i _pos) noexcept
		: position{ _pos }
	{}

	void Update() noexcept;
	void Render(const MyTexture2D& texture) const noexcept;
};