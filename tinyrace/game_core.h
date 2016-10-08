#define RENDER_COMMAND_COUNT 200
#define CHARACTER_LAYER 50

// common library includes
#include "lib_input.h"
#include "lib_RenderBuffer.h"
#include "lib_StringBuffer.h"
#include "lib_spritefont.h"
#include "lib_tilemap.h"


class NPCManager;

// a bunch of global variables that shouldn't exist in this way (sorry)
extern TinyScreen display;
extern RenderBuffer<uint16_t,RENDER_COMMAND_COUNT> buffer;

namespace Time {
    extern int millis;
}
