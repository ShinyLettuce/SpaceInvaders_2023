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

bool Game::checkForGameOver() const noexcept
{
	const auto pos = player.player_base_height;
	const auto reached_end = [pos](const Alien& a) noexcept {
		return (a.position.y > GetScreenHeight() - pos);
		};
	return (IsKeyReleased(KEY_Q) || (player.lives < 1)) || std::ranges::any_of(aliens, reached_end);
}

void Game::update()
{
	if (checkForGameOver())
	{
		return end();
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
	for (int row = 0; row < ALIEN_FORMATION_HEIGHT; row++) {
		for (int col = 0; col < ALIEN_FORMATION_WIDTH; col++) {
			const Vector2i alienPos{ FORMATION_STARTING_X + 450 + (col * ALIEN_SPACING) , FORMATION_STARTING_Y + (row * ALIEN_SPACING) };
			const Alien newAlien(alienPos);
			aliens.push_back(newAlien);
		}
	}
}

void Game::spawnWalls()
{
	const int window_width = GetScreenWidth();
	const int window_height = GetScreenHeight();
	const int wall_distance = window_width / (WALL_COUNT + 1);
	for (int i = 0; i < WALL_COUNT; i++)
	{
		const Vector2i wallPos{ wall_distance * (i + 1) , window_height - 250 };
		const Wall newWalls(wallPos);
		walls.push_back(newWalls);
	}
}

void Game::removeDeadEntities()
{
	auto isDead = [](const auto& p) { return !p.active; };
	playerProjectiles.erase(
		std::remove_if(playerProjectiles.begin(), playerProjectiles.end(), isDead),
		playerProjectiles.end());

	aliens.erase(
		std::remove_if(aliens.begin(), aliens.end(), isDead),
		aliens.end());

	walls.erase(
		std::remove_if(walls.begin(), walls.end(), isDead),
		walls.end());

	if (!enemyProjectile.active)
	{
		enemyProjectile.position = INVALID_POSITION;
		enemyProjectile.speed = 0;
	}
}

void Game::checkCollisions() noexcept
{
	for (Projectile& p : playerProjectiles)
	{
		for (Alien& a : aliens)
		{
			if (aabbCollision(a.position, a.boundingBox, p.position, p.boundingBox))
			{
				p.active = false;
				a.active = false;
				score += ALIEN_KILL_SCORE;
				break;
			}
		}
		for (Wall& w : walls)
		{
			if (aabbCollision(w.position, w.boundingBox, p.position, p.boundingBox))
			{
				p.active = false;
				w.health--;
			}
		}
	}

	if (aabbCollision({ player.x_pos, GetScreenHeight() - player.player_base_height }, player.boundingBox, enemyProjectile.position, enemyProjectile.boundingBox))
	{
		enemyProjectile.active = false;
		player.lives--;
	}

	for (Wall& w : walls)
	{
		if (aabbCollision(w.position, w.boundingBox, enemyProjectile.position, enemyProjectile.boundingBox))
		{
			enemyProjectile.active = false;
			w.health--;
		}
	}
}

void Game::createPlayerProjectile()
{
	constexpr int speed = 15;
	const auto window_height = GetScreenHeight();
	const Vector2i projectilePos{ player.x_pos, window_height - 130 };
	const Projectile newProjectile(projectilePos, speed);
	try {
		playerProjectiles.push_back(newProjectile);
	}
	catch (...) { //*swallow. game can continue without this projectile*/
	}
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