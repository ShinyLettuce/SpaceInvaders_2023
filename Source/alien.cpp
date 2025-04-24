#include "alien.h"

void Alien::Update() noexcept
{
	auto const window_width = GetScreenWidth();

	if (moveRight)
	{
		position.x += ALIEN_SPEED;

		if (position.x >= window_width)
		{
			moveRight = false;
			position.y += 50;
		}
	}
	else
	{
		position.x -= ALIEN_SPEED;

		if (position.x <= 0)
		{
			moveRight = true;
			position.y += 50;
		}
	}
}

void Alien::Render(const MyTexture2D& texture) const noexcept
{
	const int drawPosX = position.x - texture.getHalfWidth();
	const int drawPosY = position.y - texture.getHalfHeight();
	DrawTexture(texture.get(), drawPosX, drawPosY, WHITE);
}