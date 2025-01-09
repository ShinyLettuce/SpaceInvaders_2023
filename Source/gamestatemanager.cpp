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
		endScreen.finalScore = game.getScore();
		endScreen.newHighScore = endScreen.CheckNewHighScore();
	}
}

void GameStateManager::endScreenState()
{
	if (IsKeyReleased(KEY_ENTER) && !endScreen.newHighScore)
	{
		while (stateStack.top() != GameState::STARTSCREEN)
		{
			stateStack.pop();
		}
	}

	endScreen.update();
	endScreen.render();
}

void GameStateManager::update()
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