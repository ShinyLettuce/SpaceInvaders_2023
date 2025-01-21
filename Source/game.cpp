#include "game.h"

void Game::start()
{
	score = 0;
	gameOver = false;
	Player const newPlayer;
	player = newPlayer;
	spawnWalls();
	spawnAliens();
	Background newBackground;
	newBackground.Initialize(600);
	background = newBackground;
}

void Game::end() noexcept
{
	enemyProjectile.active = false;
	playerProjectiles.clear();
	walls.clear();
	aliens.clear();
	gameOver = true;
}

void Game::checkForGameOver() noexcept
{
	if (IsKeyReleased(KEY_Q))
	{
		end();
	}
	if (player.lives < 1)
	{
		end();
	}
	for (const Alien& a : aliens)
	{
		if (a.position.y > static_cast<float>(GetScreenHeight()) - player.player_base_height)
		{
			end();
		}
	}

}

void Game::update()
{
	checkForGameOver();

	player.Update();
	background.Update(-player.x_pos / 15);
	enemyProjectile.Update();
	for (Projectile& p : playerProjectiles)
	{
		p.Update();
	}
	for (Wall& w : walls)
	{
		w.Update();
	}
	for (Alien& a : aliens)
	{
		a.Update();
	}
	if (aliens.empty())
	{
		spawnAliens();
	}

	checkCollisions();

	if (IsKeyPressed(KEY_SPACE))
	{
		createPlayerProjectile();
	}

	if (!enemyProjectile.active && shootTimer > 59)
	{
		createEnemyProjectile();
		shootTimer = 0;
	}
	shootTimer++;

	removeDeadEntities();
}

void Game::render()
{
	background.Render();

	DrawText(TextFormat("Score: %i", score), 50, 20, 40, YELLOW);
	DrawText(TextFormat("Lives: %i", player.lives), 50, 70, 40, YELLOW);

	player.Render(shipTextures[player.activeTexture]);

	enemyProjectile.Render(laserTexture);
	for (const Projectile& p : playerProjectiles)
	{
		p.Render(laserTexture);
	}
	for (const Wall& w : walls)
	{
		w.Render(barrierTexture);
	}
	for (const Alien& a : aliens)
	{
		a.Render(alienTexture);
	}
}

void Game::spawnAliens()
{
	for (int row = 0; row < formationHeight; row++) {
		for (int col = 0; col < formationWidth; col++) {
			Alien newAlien;
			newAlien.active = true;
			newAlien.position.x = formationX + 450.f + (static_cast<float>(col) * alienSpacing);
			newAlien.position.y = formationY + (static_cast<float>(row) * alienSpacing);
			aliens.push_back(newAlien);
		}
	}
}

void Game::spawnWalls()
{
	const int window_width = GetScreenWidth();
	const int window_height = GetScreenHeight();
	const int wall_distance = window_width / (wallCount + 1);
	for (int i = 0; i < wallCount; i++)
	{
		const Vector2 wallPos{ static_cast<float>(wall_distance * (i + 1)) , static_cast<float>(window_height - 250) };
		const Wall newWalls(wallPos);
		walls.push_back(newWalls);
	}
}

void Game::removeDeadEntities()
{
	playerProjectiles.erase(
		std::remove_if(playerProjectiles.begin(), playerProjectiles.end(),
			[](const Projectile& p) { return !p.active; }),
		playerProjectiles.end());

	aliens.erase(
		std::remove_if(aliens.begin(), aliens.end(),
			[](const Alien& a) { return !a.active; }),
		aliens.end());

	walls.erase(
		std::remove_if(walls.begin(), walls.end(),
			[](const Wall& w) { return !w.active; }),
		walls.end());

	if (!enemyProjectile.active)
	{
		enemyProjectile.position = { -99, -99 };
		enemyProjectile.speed = 0;
	}
}

void Game::checkCollisions() noexcept
{
	for (Projectile& p : playerProjectiles)
	{
		for (Alien& a : aliens)
		{
			if (circleLineCollision(a.position, a.radius, p.lineStart, p.lineEnd))
			{
				p.active = false;
				a.active = false;
				score += 100;
			}
		}
		for (Wall& w : walls)
		{
			if (circleLineCollision(w.position, w.radius, p.lineStart, p.lineEnd))
			{
				p.active = false;
				w.health -= 1;
			}
		}
	}

	if (circleLineCollision({ player.x_pos, GetScreenHeight() - player.player_base_height }, player.radius, enemyProjectile.lineStart, enemyProjectile.lineEnd))
	{
		enemyProjectile.active = false;
		player.lives -= 1;
	}

	for (Wall& w : walls)
	{
		if (circleLineCollision(w.position, w.radius, enemyProjectile.lineStart, enemyProjectile.lineEnd))
		{
			enemyProjectile.active = false;
			w.health -= 1;
		}
	}
}

void Game::createPlayerProjectile()
{
	constexpr float speed = 15;
	const auto window_height = static_cast<float>(GetScreenHeight());
	const Vector2 projectilePos{ player.x_pos, window_height - 130 };
	const Projectile newProjectile(projectilePos, speed);
	playerProjectiles.push_back(newProjectile);
}

void Game::createEnemyProjectile() noexcept
{
	int randomAlienIndex = 0;

	if (aliens.size() > 1)
	{
		randomAlienIndex = rand() % aliens.size();
	}

	Vector2 projectilePosition = aliens[randomAlienIndex].position;
	projectilePosition.y += 40;
	enemyProjectile.position = projectilePosition;
	enemyProjectile.speed = -15;
	enemyProjectile.active = true;
}