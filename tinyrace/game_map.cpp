#include "game_core.h"
#include "game_map.h"
#include "asset_tilemap.h"
#include "lib_tilemap.h"

namespace Map {
    namespace GroundType {
        const uint8_t none = 255;
        const uint8_t misc = 0;
        const uint8_t ground = 1;
        const uint8_t forrest = 2;
        const uint8_t water = 3;
        const uint8_t sandpit = 4;
        const uint8_t road = 5;
    }
    TileMap::SceneRenderer<uint16_t,RENDER_COMMAND_COUNT> renderer;
    TileMap::Scene<uint16_t> tilemap;

    namespace {
        using namespace GroundType;

        uint8_t tileIndexGroundTypeMap[] = {
            ground, road, road, road, road, misc, none, none, none, forrest, forrest, forrest, forrest, none, none, none,
            road, road, road, road, sandpit, sandpit, sandpit, sandpit, forrest, forrest, forrest, forrest, none, none, none, none,
            road, road, road, sandpit, sandpit, sandpit, sandpit, none, forrest, forrest, forrest, none, none, none, none, none,
            water, road, road, sandpit, sandpit, sandpit, none, none, none, forrest, forrest, none, none, none, none, none,
            water, road, road, none, sandpit, sandpit, none, none, none, forrest, forrest, none, none, none, none, none,
            water, water, water, water, sandpit, sandpit, none, none, none, none, none, none, none, none, none, none,
            water, water, water, water, none, none, none, none, none, none, none, none, none, none, none, none,
            water, water, water, water, water, none, none, none, none, none, none, none, none, none, none, none,
        };
    }


    void tick() {
    }

    int getGroundType(const int x, const int y) {
        uint8_t textureXOut, textureYOut, tilemapIndex;
        int tileIndex = tilemap.getTileIndex(x, y, textureXOut, textureYOut, tilemapIndex);
        uint8_t tileSizeBits = tilemap.tileset.tileSizeBits;
        uint16_t col = tilemap.tileset.tileSets[tilemapIndex].getColor(((tileIndex & 0xf) << tileSizeBits) + textureXOut,
                                                   ((tileIndex >> 4) << tileSizeBits) + textureYOut);

        buffer.drawRect(x,y,1,1)->filledRect(col)->setDepth(160);
        return tileIndexGroundTypeMap[tileIndex];
    }

    void draw() {
        //buffer.drawRect(0,0,1,50)->filledRect(RGB565(20,40,80));
        renderer.update(buffer, tilemap, 0,0, 0,10,5);
    }
    void init() {
        tilemap = TilemapAsset::map_01();
    }

    int getWidth() {
        return tilemap.tilemaps[0].getWidth() * 16;
    }

    int getHeight() {
        return tilemap.tilemaps[0].getHeight() * 16;
    }
}
