
#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)
#include "gamestatemanager.h"

int main(void)
{    
    GameStateManager game;

    while (!WindowShouldClose())
    {
        game.run();
    }
    return 0;
}