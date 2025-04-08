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
	DrawTexture(texture.get(), position.x - texture.getWidth()/2, position.y - texture.getHeight()/2, color);
}