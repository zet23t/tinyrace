#include "game_core.h"
#include "image_data.h"

TinyScreen display = TinyScreen(TinyScreenPlus);
RenderBuffer<uint16_t,RENDER_COMMAND_COUNT> buffer;
const Texture<uint16_t> textureAtlas(ImageAsset::atlas);

namespace Time {
    int millis = 0;
}
