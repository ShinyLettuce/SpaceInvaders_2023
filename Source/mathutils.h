#pragma once
#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)
#include <algorithm>

struct Vector2i {
	int x;
	int y;
};

struct Box {
	int width;
	int height;
};

static bool constexpr aabbCollision(Vector2i pos1, Box boundingBox1, Vector2i pos2, Box boundingBox2) noexcept
{
	return (pos1.x - boundingBox1.width / 2 <= pos2.x + boundingBox2.width / 2 &&
			pos1.x + boundingBox1.width / 2 >= pos2.x - boundingBox2.width / 2 &&
			pos2.y - boundingBox2.height / 2 <= pos1.y + boundingBox1.height / 2 &&
			pos2.y + boundingBox2.height / 2 >= pos1.y - boundingBox1.height / 2);
}