#pragma once
#include <stack>
#include "game.h"

class GameStateManager
{
public:
	enum struct GameState
	{
		STARTSCREEN,
		GAMEPLAY,
		ENDSCREEN
	};


	Game game;
	std::stack<GameState> stateStack;

	void startScreen();
	void gameplay();
	void endScreen();

	void update();
};
