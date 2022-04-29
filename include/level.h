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

    inline bool parse_level();

    public:    
    
    std::vector<std::vector<int>> matrix;

    Level(std::string level_path,std::string tileset_path);
    void LoadLevel(std::string path = "");
    void DrawLevel();
    void setTileSet(Texture texture);
    
};

Level::Level(std::string level_path,std::string tileset_path){
    this->level_path = level_path;
    this->tileset_path = tileset_path;
}

bool Level::parse_level(){
    std::string token;
    bool debug = true;

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

    if(!parse_level()){
        std::cout<<"unable to load level, damaged file\n";
    }

    

}



#endif