#include "gamestatemanager.h"

void GameStateManager::startScreenState()
{
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

	EndDrawing();
}