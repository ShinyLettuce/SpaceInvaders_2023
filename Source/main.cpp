#include "raylib.h"
#include "game.h"

int main(void)
{    
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "SPACE INVADERS");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    Game game;

    InitAudioDevice(); //TODO: Do we have audio?
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        game.Update();
      
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);
        game.Render();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    CloseAudioDevice();
    
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    std::string filename = "level.txt";  //TODO: WHAT?
    return 0;
}