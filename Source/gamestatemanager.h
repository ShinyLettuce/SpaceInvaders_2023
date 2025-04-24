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
public:
	enum struct GameState
	{
		STARTSCREEN,
		GAMEPLAY,
		ENDSCREEN
	};

	explicit GameStateManager(GameState gameState) : window("SPACE INVADERS"sv)
	{
		stateStack.push(gameState);
	}

	GameStateManager() = delete;

	void run();
private:
	MyWindow window;

	Game game;
	StartScreen startScreen;
	EndScreen endScreen;
	std::stack<GameState> stateStack;


	void startScreenState();
	void gameplayState();
	void endScreenState();
};
