
#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)
#include "gamestatemanager.h"
#include <stdexcept>
#include <print>

int main(void)
{
	try {
		GameStateManager game(GameStateManager::GameState::STARTSCREEN);
		while (!WindowShouldClose())
		{
			game.run();
		}
	}
	catch (const std::runtime_error& e) {
		std::print("Runtime Error: {}", e.what());
	}
	catch (const std::exception& e) {
		std::print("Exception: {}", e.what());
	}
	catch (...)
	{
		std::print("WHAT THE FUCK?!?!");
	}
	return 0;
}