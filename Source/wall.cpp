#include "wall.h"

void Wall::Render(const MyTexture2D& texture) const noexcept
{
	DrawTexturePro(texture.get(),
		{
			0,
			0,
			704,
			704,
		},
		{
			position.x,
			position.y,
			200,
			200,
		}, { 100 , 100 },
		0,
		color);

	DrawText(TextFormat("%i", health), static_cast<int>(position.x) - 21, static_cast<int>(position.y) + 10, 40, RED);
}

void Wall::Update() noexcept
{
	if (health < 1)
	{
		active = false;
	}
}