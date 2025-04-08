#include "alien.h"

void Alien::Update() noexcept
{
	auto const window_width = static_cast<float>(GetScreenWidth());

	if (moveRight)
	{
		position.x += speed;

		if (position.x >= window_width)
		{
			moveRight = false;
			position.y += 50;
		}
	}
	else
	{
		position.x -= speed;

		if (position.x <= 0)
		{
			moveRight = true;
			position.y += 50;
		}
	}
}

void Alien::Render(const MyTexture2D& texture) const noexcept
{
	const int drawPosX = static_cast<int>(position.x) - texture.getWidth() / 2;
	const int drawPosY = static_cast<int>(position.y) - texture.getHeight() / 2;
	DrawTexture(texture.get(), drawPosX, drawPosY, color);
}