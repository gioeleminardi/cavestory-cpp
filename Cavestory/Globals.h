#ifndef GLOBALS_H
#define GLOBALS_H

namespace Globals {
    constexpr int SCREEN_WIDTH = 640;
    constexpr int SCREEN_HEIGHT = 480;

    constexpr int SPRITE_SCALE = 2;
}

enum Direction {
    LEFT,
    RIGHT,
    UP,
    DOWN
};

struct Vector2 {
    float x, y;

    Vector2() : x(0), y(0) {}

    Vector2(float x, float y) : x(x), y(y) {}

    static Vector2 zero() {
        return {0, 0};
    }
};

#endif