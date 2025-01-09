#pragma once
#include "raylib.h"
#include <algorithm>

static float lineLength(Vector2 A, Vector2 B) noexcept
{
	const float length = sqrtf(pow(B.x - A.x, 2.f) + pow(B.y - A.y, 2.f));
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

	const float dotP = (((C.x - A.x) * (B.x - A.x)) + ((C.y - A.y) * (B.y - A.y))) / pow(length, 2.f);

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