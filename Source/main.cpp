#include "raylib.h"
#include "gamestatemanager.h"

int main(void)
{    
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "SPACE INVADERS");
    SetTargetFPS(60);

    GameStateManager game;
    game.stateStack.push(GameStateManager::GameState::GAMEPLAY); //TODO: move into constructor or smtn
    InitAudioDevice(); //TODO: Do we have audio?

    while (!WindowShouldClose())
    {
        BeginDrawing();

        game.update();

        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow(); 
    std::string filename = "level.txt";  //TODO: WHAT?
    return 0;
}