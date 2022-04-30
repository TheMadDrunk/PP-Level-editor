#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "level.h";

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

    gui_rec.push_back((Rectangle){450,10,100,40});int spinner_tileset = 4;//spinner zoom tileset
    gui_rec.push_back((Rectangle){630,10,100,40});int spinner_level = 5;//spinner zoom level

    gui_rec.push_back((Rectangle){740,10,70,40});int button_save = 6; //btn to load level

    Rectangle curr_tile = {0};
    bool loaded = false;

    char* Tileset_path = new char[100];
    strcpy(Tileset_path,"Tileset path");
    char* Level_path = new char[100];
    strcpy(Level_path,"Level path");
    Texture TileSet;

    std::fstream level;
    Level level_to_edit = Level();

    Rectangle TileSet_view = (Rectangle){10,60,350,640};
    Rectangle Level_view = (Rectangle){370,60,700,640};

    int level_scale = 1;
    Camera2D level_camera;
    level_camera.offset = (Vector2){Level_view.x,Level_view.y};
    level_camera.target = (Vector2){0,0};
    level_camera.zoom = 1;
    level_camera.rotation = 0;

    Vector2 tileset_pos = (Vector2){TileSet_view.x,TileSet_view.y};
    int tileset_scale=1;
    std::cout<<"here\n";
    
    while (!WindowShouldClose())
    {

        if(IsKeyDown(KEY_A))tileset_pos.x-=6;
        if(IsKeyDown(KEY_D))tileset_pos.x+=6;
        if(IsKeyDown(KEY_S))tileset_pos.y+=6;
        if(IsKeyDown(KEY_W))tileset_pos.y-=6;

        if(IsKeyDown(KEY_UP))level_camera.offset.y-=6;
        if(IsKeyDown(KEY_DOWN))level_camera.offset.y+=6;
        if(IsKeyDown(KEY_LEFT))level_camera.offset.x-=6;
        if(IsKeyDown(KEY_RIGHT))level_camera.offset.x+=6;

        BeginDrawing();

        ClearBackground((Color){33,33,33,1});

        //focus on the clicked gui rectangle
        for(int i = 0;i<gui_rec.size();i++){
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) and CheckCollisionPointRec(GetMousePosition(),gui_rec[i])){
                focused = i;
                break;
            }
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) and CheckCollisionPointRec(GetMousePosition(),TileSet_view)){
            Vector2 mouse_pos = GetMousePosition();
           
            Rectangle tiles;
            tiles.x = tileset_pos.x;
            tiles.y = tileset_pos.y;
            tiles.width = TileSet.width * tileset_scale;
            tiles.height = TileSet.height * tileset_scale;
            if(CheckCollisionPointRec(mouse_pos,tiles)){
                curr_tile.x = (int) (mouse_pos.x-tileset_pos.x)/(level_to_edit.getTileSize()*tileset_scale)*level_to_edit.getTileSize();
                curr_tile.y = (int) (mouse_pos.y-tileset_pos.y)/(level_to_edit.getTileSize()*tileset_scale)*level_to_edit.getTileSize();
                std::cout<<curr_tile.x<<" - "<<curr_tile.y<<'\n';
            }
        }
        
        GuiTextBox(gui_rec[textbox_tileset],Tileset_path,100,focused==textbox_tileset);
        if(GuiButton(gui_rec[button_tileset],"Load")){
            TileSet = LoadTexture(Tileset_path);
            level_to_edit.setTileSet(Tileset_path);
            loaded = true;
        }

        GuiTextBox(gui_rec[textbox_level],Level_path,100,focused==textbox_level);
        if(GuiButton(gui_rec[button_level],"Load")){
            level_to_edit.LoadLevel(Level_path);
            TileSet = level_to_edit.getTileSet();
            curr_tile.width = curr_tile.height = level_to_edit.getTileSize();
            loaded = true;
        }

        GuiSpinner(gui_rec[spinner_tileset],"zoom tileset",&tileset_scale,1,20,focused==spinner_tileset);
        GuiSpinner(gui_rec[spinner_level],"zoom level",&level_scale,1,20,focused==spinner_level);
        level_camera.zoom = (int)level_scale;

        if(GuiButton(gui_rec[button_save],"Save")){
            level_to_edit.SaveLevel(Level_path);
        }
        //std::cout<<"here 2\n";
        //DrawTextureRec(TileSet,curr_tile,(Vector2){900,10},WHITE);
        DrawRectangle(899,9,42,42,LIGHTGRAY);
        if(loaded)
            DrawTextureTiled(TileSet,curr_tile,(Rectangle){900,10,40,40},(Vector2){0,0},0,5,WHITE);
        //std::cout<<"here 3\n";
        BeginScissorMode(TileSet_view.x,TileSet_view.y,TileSet_view.width,TileSet_view.height);
        ClearBackground(LIGHTGRAY);
        if(loaded)
            DrawTextureEx(TileSet,tileset_pos,0,tileset_scale,WHITE);
        EndScissorMode();
        //std::cout<<"here 4\n";

        BeginScissorMode(Level_view.x,Level_view.y,Level_view.width,Level_view.height);
        ClearBackground(BLACK);
        if(loaded)
            level_to_edit.DrawLevel(level_camera);
        EndScissorMode();
        //std::cout<<"here 5\n";

        EndDrawing();
    }

    GuiDisable();

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    delete[] Tileset_path,Level_path;

    return 0;
    
}