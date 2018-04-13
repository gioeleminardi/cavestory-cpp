//
// Created by Gioele Minardi on 13/04/18.
//

#include "Tile.h"

#include "Graphics.h"
#include "SDL.h"

Tile::Tile(SDL_Texture *tilesetTexture, Vector2 size, Vector2 position, Vector2 tilesetPosition) :
        _tilesetTexture(tilesetTexture),
        _size(size),
        _position(Vector2(position.x * Globals::SPRITE_SCALE, position.y * Globals::SPRITE_SCALE)),
        _tilesetPosition(tilesetPosition) {}

void Tile::Update(float DeltaTime) {}

void Tile::Draw(Graphics &graphics) {

    SDL_Rect sourceRect = {
            static_cast<int>(this->_tilesetPosition.x),
            static_cast<int>(this->_tilesetPosition.y),
            static_cast<int>(this->_size.x),
            static_cast<int>(this->_size.y)
    };

    SDL_Rect destRect = {
            static_cast<int>(this->_position.x),
            static_cast<int>(this->_position.y),
            static_cast<int>(this->_size.x * Globals::SPRITE_SCALE),
            static_cast<int>(this->_size.y * Globals::SPRITE_SCALE)
    };

    graphics.BlitSurface(this->_tilesetTexture, &sourceRect, &destRect);

}
