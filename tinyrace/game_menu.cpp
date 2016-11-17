#include "game_core.h"
#include "game_menu.h"
#include "font_asset.h"
#include "image_data.h"

namespace GameMenu {

    void init() {
    }
    void tick() {

    }
    void drawSprite(uint8_t x, uint8_t y, const SpriteSheetRect *rect) {
        buffer.drawRect(x,y,rect->width, rect->height)->sprite(&textureAtlas,rect->x,rect->y);
    }
    void draw() {
        buffer.drawRect(0,0,96,17)->filledRect(RGB565(255,128,0));
        buffer.drawRect(0,17,96,1)->filledRect(RGB565(255,255,255));
        buffer.drawRect(0,18,96,64)->filledRect(RGB565(64,128,255));
        drawSprite(13,1,ImageAsset::TextureAtlas_atlas::logo.sprites);
        drawSprite(33,22,ImageAsset::TextureAtlas_atlas::menu_play.sprites);
        drawSprite(83,22,ImageAsset::TextureAtlas_atlas::menu_arrow_right.sprites);
        drawSprite(13,38,ImageAsset::TextureAtlas_atlas::menu_credits.sprites);
        //buffer.drawText("Play",0,20,96,16,0,0,true, FontAsset::font, 1);

    }
}
