#include "star.h"

void Star::Update(float starOffset) noexcept
{
	position.x = initPosition.x + starOffset;
	position.y = initPosition.y;
}

void Star::Render() const noexcept
{
	DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), size, color);
}

void Background::Update(float offset) noexcept
{
	for (Star& star : Stars)
	{
		star.Update(offset);
	}
}

void Background::Render() const noexcept
{
	for (const Star& star : Stars)
	{
		star.Render();
	}
}