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
#include <string_view>

using namespace std::string_view_literals;

class GameStateManager
{
	MyWindow window;

	Game game;
	StartScreen startScreen;
	EndScreen endScreen;

	enum struct GameState
	{
		STARTSCREEN,
		GAMEPLAY,
		ENDSCREEN
	};

	GameState currentState;

	void startScreenState();
	void gameplayState();
	void endScreenState();
public:

	[[gsl::suppress(26455, justification: "We are allowed to throw if the window cannot initialize, without the window we don't have a game.")]]
	GameStateManager() : window("SPACE INVADERS"sv)
	{
		currentState = GameState::STARTSCREEN;
	}

	void run();
};
