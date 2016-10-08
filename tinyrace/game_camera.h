#ifndef __GAME_CAMERA_H__
#define __GAME_CAMERA_H__

#include "lib_FixedMath.h"

namespace Camera {
    void tick();
    void draw();
    void setPosition(Fixed2D4 pos);
}

#endif // __GAME_CAMERA_H__
