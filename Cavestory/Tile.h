//
// Created by Gioele Minardi on 13/04/18.
//

#ifndef CAVESTORY_TILE_H
#define CAVESTORY_TILE_H

#include "Globals.h"

class Graphics;
struct SDL_Texture;

class Tile {

public:
    Tile() = default;

    Tile(SDL_Texture *tilesetTexture, Vector2 size, Vector2 position, Vector2 tilesetPosition);

    virtual ~Tile() = default;

    void Update(float DeltaTime);

    void Draw(Graphics &graphics);

private:
    SDL_Texture *_tilesetTexture;
    Vector2 _size;
    Vector2 _position;
    Vector2 _tilesetPosition;
};


#endif //CAVESTORY_TILE_H
