#pragma once
#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)
#include <algorithm>

static float lineLength(Vector2 A, Vector2 B) noexcept
{
	const float length = sqrtf(powf(B.x - A.x, 2.f) + powf(B.y - A.y, 2.f));
	return length;
}

static bool pointInCircle(Vector2 circlePos, float radius, Vector2 point) noexcept
{
	const float distanceToCentre = lineLength(circlePos, point);
	return (distanceToCentre < radius);
}

static bool circleLineCollision(Vector2 circlePos, float circleRadius, Vector2 lineStart, Vector2 lineEnd) noexcept
{
	if (pointInCircle(circlePos, circleRadius, lineStart) || pointInCircle(circlePos, circleRadius, lineEnd))
	{
		return true;
	}

	const Vector2 A = lineStart;
	const Vector2 B = lineEnd;
	const Vector2 C = circlePos;

	const float length = lineLength(A, B);

	const float dotP = (((C.x - A.x) * (B.x - A.x)) + ((C.y - A.y) * (B.y - A.y))) / powf(length, 2.f);

	const float closestX = A.x + (dotP * (B.x - A.x));
	const float closestY = A.y + (dotP * (B.y - A.y));

	constexpr float buffer = 0.1f;

	const float closeToStart = lineLength(A, { closestX, closestY });
	const float closeToEnd = lineLength(B, { closestX, closestY });

	const float closestLength = closeToStart + closeToEnd;

	if (closestLength == length + buffer || closestLength == length - buffer)
	{
		const float closeToCentre = lineLength(A, { closestX, closestY });
		return (closeToCentre < circleRadius);
	}
	else
	{
		return false;
	}
}

static bool aabbCollision(Rectangle rect1, Rectangle rect2)
{
	return (rect1.x - rect1.width / 2 <= rect2.x + rect2.width / 2 &&
			rect1.x + rect1.width / 2 >= rect2.x - rect2.width / 2 &&
			rect1.y - rect1.height / 2 >= rect2.y + rect2.height / 2 &&
			rect1.y + rect1.height / 2 <= rect2.y - rect2.height / 2);
}