#ifndef __GAME_MAP_H__
#define __GAME_MAP_H__

namespace Map {
    namespace GroundType {
        extern const uint8_t ground;
        extern const uint8_t forrest;
        extern const uint8_t water;
        extern const uint8_t sandpit;
        extern const uint8_t road;
    }
    void draw();
    void tick();
    void init();
    int getWidth();
    int getHeight();
    int getGroundType(const int x, const int y);
}

#endif // __GAME_MAP_H__
