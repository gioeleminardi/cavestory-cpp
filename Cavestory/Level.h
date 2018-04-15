#ifndef LEVEL_H
#define LEVEL_H

#include "Globals.h"
#include "Tile.h"
#include <string>
#include <vector>

class Graphics;
struct SDL_Texture;
struct Tileset;

class Level
{
public:
	Level();
	Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics);
	virtual ~Level();
	void Update(float elapsedTime);
	void Draw(Graphics &graphics);

private:
	std::string _mapName;
	Vector2 _spawnPoint;
	Vector2 _mapSize;
	Vector2 _tileSize;

	std::vector<Tile> _tiles;
	std::vector<Tileset> _tilesets;

	SDL_Texture* _backgroundTexture;

	void LoadMap(std::string mapName, Graphics &graphics);
};

struct Tileset {
    SDL_Texture *texture;
    int firstGid;

    Tileset(){
        this->firstGid = -1;
    }

    Tileset(SDL_Texture *texture, int firstGid){
        this->texture = texture;
        this->firstGid = firstGid;
    }

};

#endif