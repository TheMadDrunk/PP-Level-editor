#ifndef LEVEL
#define LEVEL

#include "raylib.h"
#include <vector>
#include <fstream>
#include <iostream>

class Level
{
    private:

    std::string tileset_path;
    std::string level_path;

    int width,height;
    int tile_width,tile_height;
    int nbr_layers;
    Vector2 player_pos;

    std::fstream level_file;
    Texture tileset;

    inline void parse_level();

    public:    
    
    std::vector<std::vector<int>> matrix[5];

    Level(std::string level_path,std::string tileset_path);
    void LoadLevel(std::string path = "");
    void SaveLevel(std::string path);
    void DrawLevel();
    void setTileSet(std::string path);
    
};

Level::Level(std::string level_path,std::string tileset_path){
    this->level_path = level_path;
    this->tileset_path = tileset_path;
}

void Level::parse_level(){
    std::string token;
    bool debug = true;

    level_file >> token;
    if(debug) std::cout<<token<<'\n';
    tileset_path = token;

    level_file >> token;
    if(debug) std::cout<<token<<'\n';
    width = stoi(token);

    level_file >> token;
    if(debug) std::cout<<token<<'\n';
    height = stoi(token);

    level_file >> token;
    if(debug) std::cout<<token<<'\n';
    tile_width = stoi(token);

    level_file >> token;
    if(debug) std::cout<<token<<'\n';
    tile_height = stoi(token);

    level_file >> token;
    if(debug) std::cout<<token<<'\n';
    nbr_layers = stoi(token);

    level_file>>token;
    if(debug) std::cout<<token<<'\n';
    player_pos.x = stoi(token);
    
    level_file>>token;
    if(debug) std::cout<<token<<'\n';
    player_pos.y = stoi(token);

    int n = width/tile_width, m = height/tile_height;

    for(int i = 0;i<5;i++)matrix[i].clear();

    for(int k = 0;k<nbr_layers;k++){
        matrix[k].resize(m);
        for(int j = 0;j<m;j++){
            matrix[k][j].resize(n);
            for(int i = 0;i<n;i++){
                level_file >> token;
                matrix[k][j][i] = stoi(token);
            }
        }
    }

}

void Level::LoadLevel(std::string path=""){
    if(path.length()>0){
        this->level_path = path;
    }

    level_file.open(this->level_path,std::ios::in);
    if(!level_file.is_open()){
        std::cout<<"error : can't open file \""<<this->level_path<<"\"\n";
        return;
    }

    parse_level();
    //std::cout<<"unable to load level, damaged file\n";
    
    level_file.close();
}

void Level::SaveLevel(std::string path){
    level_file.open(path,std::ios::out | std::ios::trunc);

    level_file << width<<'\n';
    level_file <<height<<'\n';
    level_file <<tile_width<<'\n';
    level_file <<tile_height<<'\n';
    level_file <<nbr_layers<<'\n';
    level_file <<player_pos.x<<'\n';
    level_file <<player_pos.y<<'\n';

    int n = width/tile_width, m = height/tile_height;

    for(int k = 0;k<nbr_layers;k++){
        for(int j = 0;j<m;j++){
            for(int i = 0;i<n;i++){
                level_file << matrix[k][j][i];
            }
        }
    }

    level_file.close();
}

void Level::setTileSet(std::string path){
    tileset = LoadTexture(path.c_str());
}

void Level::DrawLevel(){
    
}


#endif