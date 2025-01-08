#include "gamestatemanager.h"

void GameStateManager::startScreenState()
{
	ClearBackground(BLACK);
	startScreen.render();

	if (IsKeyReleased(KEY_SPACE))
	{
		stateStack.push(GameState::GAMEPLAY);
		game.Start();
	}
}

void GameStateManager::gameplayState()
{
	game.Update();
	ClearBackground(BLACK);
	game.Render();

	if (game.gameOver)
	{
		stateStack.push(GameState::ENDSCREEN);
		endScreen.finalScore = game.score;
		endScreen.newHighScore = endScreen.CheckNewHighScore();
	}
}

void GameStateManager::endScreenState()
{
	endScreen.update();
	ClearBackground(BLACK);
	endScreen.render();

	if (IsKeyReleased(KEY_ENTER) && !endScreen.newHighScore)
	{
		while (stateStack.top() != GameState::STARTSCREEN)
		{
			stateStack.pop();
		}
	}
}

void GameStateManager::update()
{
	switch (stateStack.top())
	{
	case GameState::STARTSCREEN:
		startScreenState();
		break;
	case GameState::GAMEPLAY:
		gameplayState();
		break;
	case GameState::ENDSCREEN:
		endScreenState();
		break;
	}
}