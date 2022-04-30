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
    int focused = -1;

    gui_rec.push_back((Rectangle){10,10,100,40});int textbox_tileset = 0; //textbox to load tileset
    gui_rec.push_back((Rectangle){120,10,70,40});int button_tileset = 1; //btn to load the tileset


    gui_rec.push_back((Rectangle){200,10,100,40});int textbox_level = 2; //textbox to load level
    gui_rec.push_back((Rectangle){310,10,70,40});int button_level = 3; //btn to load level

    gui_rec.push_back((Rectangle){500,10,100,40});int spinner_tileset = 4;
    gui_rec.push_back((Rectangle){700,10,100,40});int spinner_level = 5;

    char* Tileset_path = new char[100];
    strcpy(Tileset_path,"Tileset path");
    char* Level_path = new char[100];
    strcpy(Level_path,"Level path");
    Texture TileSet = LoadTexture("tileset.png");

    std::fstream level;

    Rectangle TileSet_view = (Rectangle){10,60,350,600};

    Vector2 level_pos = (Vector2){0};
    int level_scale=1;

    Vector2 tileset_pos = (Vector2){TileSet_view.x,TileSet_view.y};
    int tileset_scale=1;
    
    while (!WindowShouldClose())
    {

        if(IsKeyDown(KEY_A))tileset_pos.x-=6;
        if(IsKeyDown(KEY_D))tileset_pos.x+=6;
        if(IsKeyDown(KEY_S))tileset_pos.y+=6;
        if(IsKeyDown(KEY_W))tileset_pos.y-=6;


        BeginDrawing();

        ClearBackground((Color){33,33,33,1});

        //focus on the clicked gui rectangle
        for(int i = 0;i<gui_rec.size();i++){
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) and CheckCollisionPointRec(GetMousePosition(),gui_rec[i])){
                focused = i;
                break;
            }
        }
        
        GuiTextBox(gui_rec[textbox_tileset],Tileset_path,100,focused==textbox_tileset);
        if(GuiButton(gui_rec[button_tileset],"Load")){
            TileSet = LoadTexture(Tileset_path);
        }

        GuiTextBox(gui_rec[textbox_level],Level_path,100,focused==textbox_level);
        if(GuiButton(gui_rec[button_level],"Load")){
            TileSet = LoadTexture(Level_path);
        }

        GuiSpinner(gui_rec[spinner_tileset],"zoom tileset",&tileset_scale,1,4,focused==spinner_tileset);
        GuiSpinner(gui_rec[spinner_level],"zoom level",&level_scale,1,4,focused==spinner_level);

        BeginScissorMode(TileSet_view.x,TileSet_view.y,TileSet_view.width,TileSet_view.height);

        ClearBackground(LIGHTGRAY);
        DrawTextureEx(TileSet,tileset_pos,0,tileset_scale,WHITE);

        EndScissorMode();

        EndDrawing();
    }

    GuiDisable();

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
    
}