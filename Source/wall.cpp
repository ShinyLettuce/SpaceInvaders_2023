#include "wall.h"

void Wall::Render(const MyTexture2D& texture) const noexcept
{
	DrawTexture(texture.get(), position.x - texture.getWidth()/2, position.y - texture.getHeight()/2, WHITE);

	DrawText(TextFormat("%i", health), position.x - 21, position.y + 10, 40, RED);
}

void Wall::Update() noexcept
{
	if (health < 1)
	{
		active = false;
	}
}