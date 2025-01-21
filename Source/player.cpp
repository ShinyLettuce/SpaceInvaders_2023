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

	x_pos += speed * direction;

	if (x_pos < 0 + radius)
	{
		x_pos = 0 + radius;
	}
	else if (x_pos > static_cast<float>(GetScreenWidth()) - radius)
	{
		x_pos = static_cast<float>(GetScreenWidth()) - radius;
	}

	timer += GetFrameTime();

	if (timer > 0.4)
	{
		activeTexture++;
		activeTexture = activeTexture % 3;
		timer = 0;
	}
}

void Player::Render(const MyTexture2D& texture) const noexcept
{
	const auto window_height = static_cast<float>(GetScreenHeight());

	DrawTexturePro(texture.get(),
		{
			0,
			0,
			352,
			352,
		},
		{
			x_pos, window_height - player_base_height,
			100,
			100,
		}, { 50, 50 },
		0,
		WHITE);
}