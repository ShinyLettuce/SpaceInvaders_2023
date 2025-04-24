#include "gamestatemanager.h"

void GameStateManager::startScreenState()
{
	startScreen.render();

	if (IsKeyReleased(KEY_SPACE))
	{
		currentState = GameState::GAMEPLAY;
		game.start();
	}
}

void GameStateManager::gameplayState()
{
	game.update();
	game.render();

	if (game.isGameOver())
	{
		currentState = GameState::ENDSCREEN;
		endScreen.setFinalScore(game.getScore());
		endScreen.setIsNewHighScore(endScreen.CheckNewHighScore());
	}
}

void GameStateManager::endScreenState()
{
	if (IsKeyReleased(KEY_ENTER) && !endScreen.getIsNewHighScore())
	{
		currentState = GameState::STARTSCREEN;
	}

	endScreen.update();
	endScreen.render();
}

void GameStateManager::run()
{
	BeginDrawing();
	ClearBackground(BLACK);

	switch (currentState)
	{
		using enum GameState;

	case STARTSCREEN:
		startScreenState();
		break;
	case GAMEPLAY:
		gameplayState();
		break;
	case ENDSCREEN:
		endScreenState();
		break;
	}

	EndDrawing();
}