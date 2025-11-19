#include "raylib.h"

int main(void){
    // Init
    const int ScreenWidth   = 640;
    const int ScreenHeight  = 480;

    InitWindow(ScreenWidth, ScreenHeight, "Hello World - Basic Window");
    
    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose()){   // Detect window close button or ESC key
        // Update
        // TODO: variables
        // Draw
        BeginDrawing();
            ClearBackground(WHITE);
            DrawText("First Window!", ScreenWidth/2, ScreenHeight/2, 20, GRAY);
        EndDrawing();
    }
    
    // De-Init
    CloseWindow();
    
    return 0;
}