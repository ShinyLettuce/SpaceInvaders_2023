#include "player.h"

void Player::Update() noexcept
{
	direction = 0;
	if (IsKeyDown(KEY_LEFT))
	{
		direction--;
	}
	if (IsKeyDown(KEY_RIGHT))
	{
		direction++;
	}

	x_pos += PLAYER_SPEED * static_cast<int>(direction);

	if (x_pos < 0 + PLAYER_BOUNDING_BOX.width / 2)
	{
		x_pos = 0 + PLAYER_BOUNDING_BOX.width / 2;
	}
	else if (x_pos > GetScreenWidth() - PLAYER_BOUNDING_BOX.width / 2)
	{
		x_pos = GetScreenWidth() - PLAYER_BOUNDING_BOX.width / 2;
	}

	timer += GetFrameTime();

	if (timer > PLAYER_ANIMATION_FRAME_TIME)
	{
		activeTexture++;
		activeTexture = activeTexture % PLAYER_ANIMATION_FRAME_COUNT;
		timer = 0;
	}
}

void Player::Render(const MyTexture2D& texture) const noexcept
{
	const auto window_height = GetScreenHeight();

	const int drawPosX = x_pos - texture.getHalfWidth();
	const int drawPosY = window_height - player_base_height - texture.getHalfWidth();
	DrawTexture(texture.get(), drawPosX, drawPosY, WHITE);
}