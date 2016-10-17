#include "lib_math.h"

#include "game_core.h"
#include "game_car.h"
#include "game_camera.h"
#include "game_map.h"
#include "game_particle.h"
#include "image_data.h"

#include "game_particle.h"

namespace Car {
    struct Car {
        Fixed2D4 pos;
        Fixed2D4 vel;
        Fixed2D4 dir;
    };

    Car car;
    int tickCounter = 0;

    void draw() {
        int x = car.pos.x.getIntegerPart();
        int y = car.pos.y.getIntegerPart();
        int dx = (car.dir.x * FixedNumber16<4>(1,9)).getIntegerPart();
        int dy = (car.dir.y * FixedNumber16<4>(1,9)).getIntegerPart();
        uint16_t col = RGB565(55,10,10);
        /*buffer.drawRect(x-1,y-1,3,3)->filledRect(col)->setDepth(15);
        buffer.drawRect(x-1+dx,y-1+dy,3,3)->filledRect(col)->setDepth(15);
        buffer.drawRect(x-1-dx,y-1-dy,3,3)->filledRect(col)->setDepth(15);*/
        const int pivotX = -8;
        const int pivotY = -8;
        FixedNumber16<4> dirModY = car.dir.y;
        // making up for missing asin transformation (for converting dot to angle) - rotation ain't linear
        if (dirModY < 0 && dirModY.getFractionPart() > 2 && dirModY.getFractionPart() < 7) dirModY += FixedNumber16<4>(0,3);
        if (dirModY < 0 && dirModY.getFractionPart() > 11 && dirModY.getFractionPart() < 13) dirModY -= FixedNumber16<4>(0,1);
        if (dirModY > 0 && dirModY.getFractionPart() > 2 && dirModY.getFractionPart() < 9) dirModY -= FixedNumber16<4>(0,3);
        if (dirModY > 0 && dirModY.getFractionPart() > 8 && dirModY.getFractionPart() < 13) dirModY -= FixedNumber16<4>(0,1);
        int dir = 8-((dirModY + FixedNumber16<4>(1,0)) * FixedNumber16<4>(4,0)).getIntegerPart();
        if (dir < 0) dir = 0;
        if (dir > 8) dir = 8;
        if (car.dir.x < 0) dir = 16 - dir;

        SpriteSheetRect rect = ImageAsset::TextureAtlas_atlas::racingcar.sprites[(dir + 8) % 16];
        buffer.drawRect(rect.offsetX+x+pivotX,rect.offsetY+y+pivotY,rect.width,rect.height)->sprite(&textureAtlas,rect.x,rect.y)->setDepth(30);

    }
    void tick() {
        tickCounter += 1;
        Fixed2D4 stick = Joystick::getJoystick();
        if (stick.dot(car.dir) < 0) {
            Fixed2D4 left = stick.left();
            Fixed2D4 right = stick.right();
            if (left.dot(car.dir) > right.dot(car.dir)) {
                stick = left;
            } else {
                stick = right;
            }
        }
        FixedNumber16<4> len = stick.length();// * FixedNumber16<4>(0,12);
        if (len.getFractionPart() > 5) len.setFractionPart(5);
        stick.normalize();
        stick.scale(len);
        //printf("%d %d\n", len.getIntegerPart(),len.getFractionPart());
        //stick.normalize();

        if (tickCounter % 2 == 0) {

            car.dir += stick * FixedNumber16<4>(1,8);
            car.dir.normalize();
        }
        //if (car.dir.x < 0) car.dir.x += FixedNumber16<4>(0,1);
        //if (car.dir.y < 0) car.dir.y += FixedNumber16<4>(0,1);
        //printf("v0: %f %f\n",car.vel.x.asFloat(), car.vel.y.asFloat());
        //printf("d0: %f %f\n",car.dir.x.asFloat(), car.dir.y.asFloat());
        car.vel.scale(FixedNumber16<4>(0,15));
        //printf("v1: %f %f\n",car.vel.x.asFloat(), car.vel.y.asFloat());
        //printf("d1: %f %f\n",car.dir.x.asFloat(), car.dir.y.asFloat());
        car.vel+=car.dir * len;
        if (car.vel.x < 0) car.vel.x+=FixedNumber16<4>(0,1);
        if (car.vel.y < 0) car.vel.y+=FixedNumber16<4>(0,1);
        if (car.vel.x > 0) car.vel.x-=FixedNumber16<4>(0,1);
        if (car.vel.y > 0) car.vel.y-=FixedNumber16<4>(0,1);
        //printf("%d %d\n",car.vel.x.getFractionPart(),car.vel.y.getFractionPart());
        car.pos += car.vel;
        if (car.pos.x < FixedNumber16<4>(96+32,0)) car.pos.x = FixedNumber16<4>(96+32,0);
        if (car.pos.y < FixedNumber16<4>(64+32,0)) car.pos.y = FixedNumber16<4>(64+32,0);
        if (car.pos.x > FixedNumber16<4>(Map::getWidth()-32,0)) car.pos.x = FixedNumber16<4>(Map::getWidth()-32,0);
        if (car.pos.y > FixedNumber16<4>(Map::getHeight()-32,0)) car.pos.y = FixedNumber16<4>(Map::getHeight()-32,0);
        Camera::setPosition(car.pos + car.vel * 5 + car.dir * 3);
        //printf(" %f %f\n",car.vel.length().asFloat(), len.asFloat());
        if (tickCounter%2 == 0) {
            uint32_t rx = Math::randInt();
            uint32_t ry = Math::randInt();
            Particle::spawn(car.pos - car.dir * FixedNumber16<4>(6,0),
                            car.vel * FixedNumber16<4>(0,12) + Fixed2D4(FixedNumber16<4>(0,(rx%5)), FixedNumber16<4>(0,ry%5)).scale(FixedNumber16<4>(rx & 256 ? 1 : -1,0)),0,
                            (car.vel.length() * FixedNumber16<4>(6,0)).getIntegerPart() + 1);
        }
    }
    void init() {
        car.pos.x.setIntegerPart(30);
        car.pos.y.setIntegerPart(30);
        car.dir.x.setIntegerPart(1);
    }
}
