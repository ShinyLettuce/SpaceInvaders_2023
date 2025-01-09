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

void Background::Initialize(int starAmount)
{
	for (int i = 0; i < starAmount; i++)
	{
		const Star newStar;
		Stars.push_back(newStar);
	}
}

void Background::Update(float offset) noexcept
{
	for (Star& star : Stars)
	{
		star.Update(offset);
	}
}

void Background::Render()
{
	for (Star& star : Stars)
	{
		star.Render();
	}
}