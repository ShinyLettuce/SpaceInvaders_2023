#pragma once
#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)
#include "mytexture2d.h"
#include "mathutils.h"

struct Projectile
{
public:
	int speed = 15;
	bool active = true;
	Vector2i position = { 0,0 };

	Projectile(Vector2i _position, int _speed) noexcept : 
		speed{_speed},
		position{ _position }
	{}

	void Update() noexcept;
	void Render(const MyTexture2D& texture) const noexcept;
};