#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"


#define S_WIDTH 1080
#define S_HEIGHT 720

int main(){
    InitWindow(S_WIDTH,S_HEIGHT,"PP : Level Editor");    
    SetTargetFPS(60);
    GuiEnable();  

    std::vector<Rectangle> gui_rec;
    int focused = 0;

    gui_rec.push_back((Rectangle){10,10,100,40});int textbox_tileset = 0; //textbox to load tileset
    gui_rec.push_back((Rectangle){120,10,70,40});int button_tileset = 1; //btn to load the tileset


    gui_rec.push_back((Rectangle){200,10,100,40});int textbox_level = 2; //textbox to load level
    gui_rec.push_back((Rectangle){310,10,70,40});int button_level = 3; //btn to load level

    char* Tileset_path = new char[100];
    strcpy(Tileset_path,"Tileset path");
    char* Level_path = new char[100];
    strcpy(Level_path,"Level path");
    Texture TileSet;

    std::fstream level;

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(DARKGRAY);

        //focus on the clicked gui rectangle
        for(int i = 0;i<gui_rec.size();i++){
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) and CheckCollisionPointRec(GetMousePosition(),gui_rec[i])){
                focused = i;
                break;
            }
        }

        
        GuiTextBox(gui_rec[textbox_tileset],Tileset_path,100,focused==0);
        if(GuiButton(gui_rec[button_tileset],"Load")){
            TileSet = LoadTexture(Tileset_path);
        }

        GuiTextBox(gui_rec[textbox_level],Level_path,100,focused==0);
        if(GuiButton(gui_rec[button_level],"Load")){
            TileSet = LoadTexture(Level_path);
        }

        DrawTexture(TileSet,10,60,WHITE);


        EndDrawing();
    }

    GuiDisable();

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
    
}