#include "game_camera.h"
#include "game_core.h"

namespace Camera {
    static Fixed2D4 pos;

    void tick() {
    }

    void setPosition(Fixed2D4 p) {
        pos = p;
    }

    void draw() {
        buffer.setOffset(0,0);
        buffer.drawRect(48,32-1,1,3)->filledRect(RGB565(128,0,0))->setDepth(15);
        buffer.drawRect(48-1,32,3,1)->filledRect(RGB565(128,0,0))->setDepth(15);
        buffer.setOffset(pos.x.getIntegerPart()-48, pos.y.getIntegerPart()-32);
    }

}
