#include "raylib.h"

int main(void){
    // Init
    const int ScreenWidth   = 640;
    const int ScreenHeight  = 480;
    Vector2 pos = {0, 0};

    InitWindow(ScreenWidth, ScreenHeight, "Hello World - Basic Window");
    
    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose()){   // Detect window close button or ESC key
        float deltaTime = GetFrameTime();
        // Update
        // TODO: variables
        if(IsKeyDown(KEY_UP)){pos.y -= 10.0f * deltaTime;}
        if(IsKeyDown(KEY_DOWN)){pos.y += 10.0f * deltaTime; }
        if(IsKeyDown(KEY_LEFT)){pos.x -= 10.0f * deltaTime; }
        if(IsKeyDown(KEY_RIGHT)){pos.x += 10.0f * deltaTime; }
        // Draw
        BeginDrawing();
            ClearBackground(WHITE);
            DrawText("First Window!", pos.x, pos.y, 20, GRAY);
        EndDrawing();
    }
    
    // De-Init
    CloseWindow();
    
    return 0;
}