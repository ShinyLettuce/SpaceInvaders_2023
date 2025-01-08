#include "gamestatemanager.h"

void GameStateManager::startScreen()
{

}

void GameStateManager::gameplay()
{
	game.Update();
	ClearBackground(BLACK);
	game.Render();
}

void GameStateManager::endScreen()
{

}

void GameStateManager::update()
{
	switch (stateStack.top())
	{
	case GameState::STARTSCREEN:
		startScreen();
		break;
	case GameState::GAMEPLAY:
		gameplay();
		break;
	case GameState::ENDSCREEN:
		endScreen();
		break;
	}
}