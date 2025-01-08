#include "game.h"

// MATH FUNCTIONS
float lineLength(Vector2 A, Vector2 B)
{
	float length = sqrtf(pow(B.x - A.x, 2) + pow(B.y - A.y, 2));

	return length;
}

bool pointInCircle(Vector2 circlePos, float radius, Vector2 point)
{
	float distanceToCentre = lineLength(circlePos, point);

	if (distanceToCentre < radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Game::Start()
{
	gameOver = false;
	// creating walls 
	const int window_width = GetScreenWidth();
	const int window_height = GetScreenHeight();
	const int wall_distance = window_width / (wallCount + 1);
	for (int i = 0; i < wallCount; i++)
	{
		Wall newWalls;
		newWalls.position.y = window_height - 250;
		newWalls.position.x = wall_distance * (i + 1);

		Walls.push_back(newWalls);

	}

	Player const newPlayer;
	player = newPlayer;

	SpawnAliens();

	Background newBackground;
	newBackground.Initialize(600);
	background = newBackground;
	score = 0;
}

void Game::End()
{
	enemyProjectiles.clear();
	playerProjectiles.clear();
	Walls.clear();
	Aliens.clear();
	gameOver = true;
}

void Game::Update() //TODO: split into several functions
{
	if (IsKeyReleased(KEY_Q))
	{
		End();
	}

	player.Update();

	for (Alien& a : Aliens)
	{
		a.Update();

		if (a.position.y > GetScreenHeight() - player.player_base_height)
		{
			End();
		}
	}

	if (player.lives < 1)
	{
		End();
	}

	if (Aliens.empty())
	{
		SpawnAliens();
	}

	// Update background with offset
	playerPos = { player.x_pos, player.player_base_height };
	cornerPos = { 0, player.player_base_height };
	offset = lineLength(playerPos, cornerPos) * -1;
	background.Update(offset / 15);

	for (Projectile& p : playerProjectiles)
	{
		p.Update();
	}
	for (Projectile& p : enemyProjectiles)
	{
		p.Update();
	}
	for (Wall& w : Walls)
	{
		w.Update();
	}

	checkCollisions();

	if (IsKeyPressed(KEY_SPACE))
	{
		createPlayerProjectile();
	}

	shootTimer += 1;
	if (shootTimer > 59)
	{
		createEnemyProjectile();
		shootTimer = 0;
	}

	removeDeadEntities();
}

void Game::Render()
{
	background.Render();

	DrawText(TextFormat("Score: %i", score), 50, 20, 40, YELLOW);
	DrawText(TextFormat("Lives: %i", player.lives), 50, 70, 40, YELLOW);

	player.Render(shipTextures[player.activeTexture]);

	for (Projectile& p : playerProjectiles)
	{
		p.Render(laserTexture);
	}
	for (Projectile& p : enemyProjectiles)
	{
		p.Render(laserTexture);
	}

	for (Wall& w : Walls)
	{
		w.Render(barrierTexture);
	}

	for (const Alien& a : Aliens)
	{
		a.Render(alienTexture);
	}
}

void Game::SpawnAliens()
{
	for (int row = 0; row < formationHeight; row++) {
		for (int col = 0; col < formationWidth; col++) {
			Alien newAlien;
			newAlien.active = true;
			newAlien.position.x = formationX + 450 + (col * alienSpacing);
			newAlien.position.y = formationY + (row * alienSpacing);
			Aliens.push_back(newAlien);
			std::cout << "Find Alien -X:" << newAlien.position.x << std::endl;
			std::cout << "Find Alien -Y:" << newAlien.position.y << std::endl;
		}
	}
}

void Game::removeDeadEntities()
{
	playerProjectiles.erase(
		std::remove_if(playerProjectiles.begin(), playerProjectiles.end(),
			[](const Projectile& p) { return !p.active; }),
		playerProjectiles.end());

	enemyProjectiles.erase(
		std::remove_if(enemyProjectiles.begin(), enemyProjectiles.end(),
			[](const Projectile& p) { return !p.active; }),
		enemyProjectiles.end());

	Aliens.erase(
		std::remove_if(Aliens.begin(), Aliens.end(),
			[](const Alien& a) { return !a.active; }),
		Aliens.end());

	Walls.erase(
		std::remove_if(Walls.begin(), Walls.end(),
			[](const Wall& w) { return !w.active; }),
		Walls.end());
}

void Game::checkCollisions()
{
	for (Projectile& p : playerProjectiles)
	{
		for (Alien& a : Aliens)
		{
			if (circleLineCollision(a.position, a.radius, p.lineStart, p.lineEnd))
			{
				p.active = false;
				a.active = false;
				score += 100;
			}
		}
		for (Wall& w : Walls)
		{
			if (circleLineCollision(w.position, w.radius, p.lineStart, p.lineEnd))
			{
				p.active = false;
				w.health -= 1;
			}
		}
	}
	for (Projectile& p : enemyProjectiles)
	{

		if (circleLineCollision({ player.x_pos, GetScreenHeight() - player.player_base_height }, player.radius, p.lineStart, p.lineEnd))
		{
			p.active = false;
			player.lives -= 1;
		}

		for (Wall& w : Walls)
		{
			if (circleLineCollision(w.position, w.radius, p.lineStart, p.lineEnd))
			{
				p.active = false;
				w.health -= 1;
			}
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

	if (Aliens.size() > 1)
	{
		randomAlienIndex = rand() % Aliens.size();
	}

	Vector2 projectilePosition = Aliens[randomAlienIndex].position;
	projectilePosition.y += 40;
	const float projectileSpeed = -15;
	const Projectile newProjectile(projectilePosition, projectileSpeed);
	enemyProjectiles.push_back(newProjectile);
}

bool Game::circleLineCollision(Vector2 circlePos, float circleRadius, Vector2 lineStart, Vector2 lineEnd)
{
	if (pointInCircle(circlePos, circleRadius, lineStart) || pointInCircle(circlePos, circleRadius, lineEnd))
	{
		return true;
	}

	const Vector2 A = lineStart;
	const Vector2 B = lineEnd;
	const Vector2 C = circlePos;

	const float length = lineLength(A, B);

	const float dotP = (((C.x - A.x) * (B.x - A.x)) + ((C.y - A.y) * (B.y - A.y))) / pow(length, 2);

	const float closestX = A.x + (dotP * (B.x - A.x));
	const float closestY = A.y + (dotP * (B.y - A.y));

	constexpr float buffer = 0.1f;

	const float closeToStart = lineLength(A, { closestX, closestY });
	const float closeToEnd = lineLength(B, { closestX, closestY });

	const float closestLength = closeToStart + closeToEnd;

	if (closestLength == length + buffer || closestLength == length - buffer)
	{
		const float closeToCentre = lineLength(A, { closestX, closestY });

		if (closeToCentre < circleRadius)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}