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
	DrawTexturePro(texture.get(),
		{
			0,
			0,
			352,
			352,
		},
		{
			position.x,
			position.y,
			100,
			100,
		}, { 50 , 50 },
		0,
		color);
}