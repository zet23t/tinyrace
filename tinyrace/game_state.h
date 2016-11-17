#ifndef __GAME_STATE_H__
#define __GAME_STATE_H__

#include <inttypes.h>

namespace GameState {
    namespace Mode {
        extern const uint8_t MainMenu;
        extern const uint8_t Race;
    }
    void setMode(uint8_t mode);
    void init();
    void tick();
}


#endif // __GAME_STATE_H__
