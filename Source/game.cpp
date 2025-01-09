#include "game.h"

// MATH FUNCTIONS
static float lineLength(Vector2 A, Vector2 B) noexcept
{
	const float length = sqrtf(pow(B.x - A.x, 2.f) + pow(B.y - A.y, 2.f));
	return length;
}

static bool pointInCircle(Vector2 circlePos, float radius, Vector2 point) noexcept
{
	const float distanceToCentre = lineLength(circlePos, point);
	return (distanceToCentre < radius);
}

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

void Game::update() //TODO: split into several functions
{
	if (IsKeyReleased(KEY_Q))
	{
		end();
	}

	player.Update();

	for (Alien& a : aliens)
	{
		a.Update();

		if (a.position.y > static_cast<float>(GetScreenHeight()) - player.player_base_height)
		{
			end();
		}
	}

	if (player.lives < 1)
	{
		end();
	}

	if (aliens.empty())
	{
		spawnAliens();
	}

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
			newAlien.position.x = formationX + 450.f + (col * alienSpacing);
			newAlien.position.y = formationY + (row * alienSpacing);
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
		Wall newWalls;
		newWalls.position.y = window_height - 250;
		newWalls.position.x = wall_distance * (i + 1);

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
	const auto window_height = static_cast<float>(GetScreenHeight());
	constexpr float speed = 15;
	const Vector2 projectilePos{ player.x_pos, window_height - 130 };
	const Projectile newProjectile(projectilePos, speed);
	playerProjectiles.push_back(newProjectile);
}

void Game::createEnemyProjectile()
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

bool Game::circleLineCollision(Vector2 circlePos, float circleRadius, Vector2 lineStart, Vector2 lineEnd) const noexcept
{
	if (pointInCircle(circlePos, circleRadius, lineStart) || pointInCircle(circlePos, circleRadius, lineEnd))
	{
		return true;
	}

	const Vector2 A = lineStart;
	const Vector2 B = lineEnd;
	const Vector2 C = circlePos;

	const float length = lineLength(A, B);

	const float dotP = (((C.x - A.x) * (B.x - A.x)) + ((C.y - A.y) * (B.y - A.y))) / pow(length, 2.f);

	const float closestX = A.x + (dotP * (B.x - A.x));
	const float closestY = A.y + (dotP * (B.y - A.y));

	constexpr float buffer = 0.1f;

	const float closeToStart = lineLength(A, { closestX, closestY });
	const float closeToEnd = lineLength(B, { closestX, closestY });

	const float closestLength = closeToStart + closeToEnd;

	if (closestLength == length + buffer || closestLength == length - buffer)
	{
		const float closeToCentre = lineLength(A, { closestX, closestY });
		return (closeToCentre < circleRadius);
	}
	else
	{
		return false;
	}
}