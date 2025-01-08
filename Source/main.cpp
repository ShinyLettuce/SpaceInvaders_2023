#include "raylib.h"
#include "gamestatemanager.h"

int main(void)
{    
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "SPACE INVADERS");
    SetTargetFPS(60);

    GameStateManager game;
    InitAudioDevice(); //TODO: Do we have audio?

    while (!WindowShouldClose())
    {
        game.update();
    }

    CloseAudioDevice();
    CloseWindow(); 
    std::string filename = "level.txt";  //TODO: WHAT?
    return 0;
}