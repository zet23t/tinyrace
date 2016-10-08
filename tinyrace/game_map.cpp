#include "game_core.h"
#include "game_map.h"
#include "asset_tilemap.h"
#include "lib_tilemap.h"

namespace Map {
    TileMap::SceneRenderer<uint16_t,RENDER_COMMAND_COUNT> renderer;
    TileMap::Scene<uint16_t> tilemap;

    void tick() {
    }

    void draw() {
        buffer.drawRect(0,0,1,50)->filledRect(RGB565(20,40,80));
        renderer.update(buffer, tilemap, 0,0, 0,10,5);
    }
    void init() {
        tilemap = TilemapAsset::map_01();
    }
}
