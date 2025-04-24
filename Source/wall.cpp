#include "wall.h"

void Wall::Render(const MyTexture2D& texture) const noexcept
{
	DrawTexture(texture.get(), position.x - texture.getHalfWidth(), position.y - texture.getHalfHeight(), WHITE);
	const Vector2i wallTextPos = { position.x - WALL_TEXT_X_OFFSET, position.y + WALL_TEXT_Y_OFFSET };
	DrawText(TextFormat("%i", health), wallTextPos.x, wallTextPos.y, WALL_TEXT_FONT_SIZE, RED);
}

void Wall::Update() noexcept
{
	if (health < 1)
	{
		active = false;
	}
}