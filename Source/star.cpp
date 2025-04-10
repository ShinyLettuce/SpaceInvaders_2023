#include "star.h"

void Star::Update(int starOffset) noexcept
{
	position.x = initPosition.x + starOffset;
	position.y = initPosition.y;
}

void Star::Render() const noexcept
{
	DrawCircle(position.x, position.y, static_cast<float>(size), color);
}

void Background::Update(int offset) noexcept
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