
#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)
#include "gamestatemanager.h"

int main(void)
{    
    constexpr int screenWidth = 1920;
    constexpr int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "SPACE INVADERS");
    SetTargetFPS(60);
    GameStateManager game;

    while (!WindowShouldClose())
    {
        game.run();
    }
    CloseWindow(); 
    return 0;
}