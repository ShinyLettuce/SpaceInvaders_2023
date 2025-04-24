#include "projectile.h"

void Projectile::Update() noexcept
{
	position.y -= speed;

	if (position.y < 0 || position.y > 1500)
	{
		active = false;
	}
}

void Projectile::Render(const MyTexture2D& texture) const noexcept
{
	const int drawPosX = position.x - texture.getHalfWidth();
	const int drawPosY = position.y - texture.getHalfHeight();
	DrawTexture(texture.get(), drawPosX, drawPosY, WHITE);
}