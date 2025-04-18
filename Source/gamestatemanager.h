#pragma once
#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)
#include <stack>
#include "game.h"
#include "startscreen.h"
#include "endscreen.h"
#include "mywindow.h"

class GameStateManager
{
	MyWindow window;

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
