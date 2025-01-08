#include "raylib.h"
#include "gamestatemanager.h"

int main(void)
{    
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "SPACE INVADERS");
    SetTargetFPS(60);
    GameStateManager game;

    while (!WindowShouldClose())
    {
        game.update();
    }
    CloseWindow(); 
    return 0;
}