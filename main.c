#include "raylib.h"
#include <stdlib.h>

int main(){
    const int screenWidth = 1280;
    const int screenHeight = 720;

    // Initializing Game Board and assigning each square a random number
    const int rows = screenHeight/10;
    const int columns = screenWidth/10;

    int cells[rows][columns];
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            cells[i][j] = rand() % 2;
        }
    }

    int cellsCopy[rows][columns];
    int liveNeighbors = 0;
    int frameCounter = 0;

    InitWindow(screenWidth, screenHeight, "Practicing Raylib :)");
    SetTargetFPS(30);

    // Displaying starting logo
    while(frameCounter < 120){
        BeginDrawing();
        frameCounter++;
        DrawRectangle(0, 0, screenWidth, screenHeight, GREEN);
        DrawText("GAME OF LIFE", 100, screenHeight/2, 80, BLACK);
        DrawText("You can reset the board by pressing 'R' :)", screenWidth - 1000, screenHeight/2 + 80, 30, BLACK);
        EndDrawing();
    }

    while(!WindowShouldClose()){

        // Resetting the board if R is pressed
        if(IsKeyPressed(KEY_R)){
            for(int i = 0; i < rows; i++){
                for(int j = 0; j < columns; j++){
                    cells[i][j] = rand() % 2;
                }
            }
        }
        
        BeginDrawing();
            ClearBackground(RAYWHITE);

            // Drawing the Game Board
            for(int i = 0; i < rows; i++){
                for(int j = 0; j < columns; j++){
                    if(cells[i][j] == 1){
                        DrawRectangle(j * 10, i * 10, 10, 10, BLACK);
                    }
                }
            } 
        EndDrawing();

        // Copying the game board for next generation
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                cellsCopy[i][j] = cells[i][j];
            }
        }
        // Updating square states based on rules of GOL
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                // counting living neighbors
                liveNeighbors = 0;
                if(cellsCopy[i][j+1] == 1)
                    liveNeighbors++;
                if(cellsCopy[i+1][j+1] == 1)
                    liveNeighbors++;
                if(cellsCopy[i-1][j+1] == 1)
                    liveNeighbors++;
                if(cellsCopy[i][j-1] == 1)
                    liveNeighbors++;
                if(cellsCopy[i-1][j] == 1)
                    liveNeighbors++;
                if(cellsCopy[i+1][j] == 1)
                    liveNeighbors++;
                if(cellsCopy[i-1][j-1] == 1)
                    liveNeighbors++;
                if(cellsCopy[i+1][j-1] == 1)
                    liveNeighbors++;

                // Implementing rules based on neighbor-count
                if(liveNeighbors < 2 || liveNeighbors > 3){
                    cells[i][j] = 0;
                } else if(liveNeighbors == 3){
                    cells[i][j] = 1;
                }
            }
        }

    }

    CloseWindow();
    return 0;
}