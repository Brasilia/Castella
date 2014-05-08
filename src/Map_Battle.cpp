#include <Map_Battle.hpp>

Map_Battle::Map_Battle(int width, int height)
{
    //Initialize map with the terrain tags
    this->width = width;
    this->height = height;
    int mapMatrix[width][height];
    SDL_Surface *grass = tiles.push("images/tiles/grass.png");
    SDL_Surface *dirt = tiles.push("images/tiles/dirt.png");
    SDL_Surface *stone = tiles.push("images/tiles/stone.png");
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            if(i==6 && j==14){ //dirt
                tileMap.push_back(MapTile(j,i,TRR_DIRT));
                tileMap[i*width+j].set_terrain_image(dirt);
                mapMatrix[i][j] = TRR_DIRT;
            }
            else if(i==0 || i==height-1){
                tileMap.push_back(MapTile(j,i,TRR_STONE));
                tileMap[i*width+j].set_terrain_image(stone);
                mapMatrix[i][j] = TRR_STONE;
            }
            else{ //grass
                tileMap.push_back(MapTile(j,i,TRR_GRASS));
                tileMap[i*width+j].set_terrain_image(grass);
                mapMatrix[i][j] = TRR_GRASS;
            }
        }
    }

}
Map_Battle::Map_Battle(std::string filename){
    //load map from file
}

Map_Battle::~Map_Battle()
{
    //dtor
}

void Map_Battle::draw(SDL_Surface *screen){
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            tileMap[i*width+j].draw(screen);
        }
    }
}
