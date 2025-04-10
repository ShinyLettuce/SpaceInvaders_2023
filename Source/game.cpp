#include "game.h"

void Game::start()
{
	score = 0;
	gameOver = false;
	Player const newPlayer;
	player = newPlayer;
	spawnWalls();
	spawnAliens();
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
		if (a.position.y > GetScreenHeight() - player.player_base_height)
		{
			end();
		}
	}
}

void Game::update()
{
	checkForGameOver();
	if (gameOver)
	{
		return;
	}

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

void Game::render() noexcept
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
			const Vector2i alienPos{ formationX + 450 + (col * alienSpacing) , formationY + (row * alienSpacing) };
			const Alien newAlien(alienPos);
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
		const Vector2i wallPos{ wall_distance * (i + 1) , window_height - 250 };
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
			if (aabbCollision(a.position, a.boundingBox,  p.position, p.boundingBox))
			{
				p.active = false;
				a.active = false;
				score += 100;
				break;
			}
		}
		for (Wall& w : walls)
		{
			if (aabbCollision(w.position, w.boundingBox, p.position, p.boundingBox))
			{
				p.active = false;
				w.health -= 1;
			}
		}
	}

	if (aabbCollision({ player.x_pos, GetScreenHeight() - player.player_base_height }, player.boundingBox, enemyProjectile.position, enemyProjectile.boundingBox))
	{
		enemyProjectile.active = false;
		player.lives -= 1;
	}

	for (Wall& w : walls)
	{
		if (aabbCollision(w.position, w.boundingBox, enemyProjectile.position, enemyProjectile.boundingBox))
		{
			enemyProjectile.active = false;
			w.health -= 1;
		}
	}
}

void Game::createPlayerProjectile()
{
	constexpr int speed = 15;
	const auto window_height = GetScreenHeight();
	const Vector2i projectilePos{ player.x_pos, window_height - 130 };
	const Projectile newProjectile(projectilePos, speed);
	playerProjectiles.push_back(newProjectile);
}

void Game::createEnemyProjectile()
{
	int randomAlienIndex = 0;

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0, INT16_MAX);

	if (aliens.size() > 1)
	{
		randomAlienIndex = distribution(generator) % aliens.size();
	}

	Vector2i projectilePosition = aliens[randomAlienIndex].position;
	projectilePosition.y += 40;
	enemyProjectile.position = projectilePosition;
	enemyProjectile.speed = -15;
	enemyProjectile.active = true;
}