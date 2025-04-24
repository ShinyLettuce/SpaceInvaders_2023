#include "gamestatemanager.h"

void GameStateManager::startScreenState()
{
	startScreen.render();

	if (IsKeyReleased(KEY_SPACE))
	{
		stateStack.push(GameState::GAMEPLAY);
		game.start();
	}
}

void GameStateManager::gameplayState()
{
	game.update();
	game.render();

	if (game.isGameOver())
	{
		stateStack.push(GameState::ENDSCREEN);
		endScreen.setFinalScore(game.getScore());
		endScreen.setIsNewHighScore(endScreen.CheckNewHighScore());
	}
}

void GameStateManager::endScreenState()
{
	if (IsKeyReleased(KEY_ENTER) && !endScreen.getIsNewHighScore())
	{
		while (!stateStack.empty())
		{
			stateStack.pop();
		}
		stateStack.push(GameState::STARTSCREEN);
	}

	endScreen.update();
	endScreen.render();
}

void GameStateManager::run()
{
	BeginDrawing();
	ClearBackground(BLACK);

	switch (stateStack.top())
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