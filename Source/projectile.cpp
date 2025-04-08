#include "projectile.h"

void Projectile::Update() noexcept
{
	position.y -= speed;
	lineStart.y = position.y - 15;
	lineEnd.y = position.y + 15;

	lineStart.x = position.x;
	lineEnd.x = position.x;

	if (position.y < 0 || position.y > 1500)
	{
		active = false;
	}
}

void Projectile::Render(const MyTexture2D& texture) const noexcept
{
	DrawTexture(texture.get(), position.x - texture.getWidth()/2, position.y - texture.getHeight()/2, WHITE);
}