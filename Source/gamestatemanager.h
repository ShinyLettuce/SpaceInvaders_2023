#pragma once
#include <stack>
#include "raylib.h"
#include "game.h"
#include "startscreen.h"
#include "endscreen.h"

class GameStateManager
{
	enum struct GameState
	{
		STARTSCREEN,
		GAMEPLAY,
		ENDSCREEN
	};

	Game game;
	StartScreen startScreen;
	EndScreen endScreen;
	std::stack<GameState> stateStack;

	void startScreenState();
	void gameplayState();
	void endScreenState();
public:

	GameStateManager()
	{
		stateStack.push(GameState::STARTSCREEN);
	}

	void run();
};
