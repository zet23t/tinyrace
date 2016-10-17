#ifndef __GAME_PARTICLE_H__
#define __GAME_PARTICLE_H__

#include "lib_FixedMath.h"

#define MAX_PARTICLES 32

namespace Particle {

    void spawn (Fixed2D4 pos, Fixed2D4 vel, uint8_t type, uint16_t maxAge);
    void init();
    void tick();
    void draw();
}

#endif // __GAME_PARTICLE_H__
