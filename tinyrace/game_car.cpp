#include "lib_math.h"

#include "game_core.h"
#include "game_car.h"
#include "game_camera.h"
#include "game_map.h"
#include "game_particle.h"
#include "image_data.h"

#include "game_particle.h"

namespace Car {
    struct GroundProperties {
        FixedNumber16<4> friction;
        uint8_t particleType;
        bool solid;

        void init(int frictionFrac, uint8_t particleType, bool s) {
            friction.setFractionPart(frictionFrac);
            this->particleType = particleType;
            this->solid = s;
        }
    };
    struct Car {
        Fixed2D4 pos;
        Fixed2D4 vel;
        Fixed2D4 dir;
        GroundProperties groundType;
    };

    GroundProperties groundProperties[8];

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

        int groundTypeFront = Map::getGroundType(car.pos.x.getIntegerPart() + (car.dir.x * 4).getIntegerPart(), car.pos.y.getIntegerPart() + (car.dir.y * 4).getIntegerPart());
        int groundTypeBack = Map::getGroundType(car.pos.x.getIntegerPart() - (car.dir.x * 4).getIntegerPart(), car.pos.y.getIntegerPart() - (car.dir.y * 4).getIntegerPart());
        GroundProperties propFront = groundProperties[groundTypeFront];
        GroundProperties propBack = groundProperties[groundTypeBack];
        car.groundType = propFront;

        //if (car.dir.x < 0) car.dir.x += FixedNumber16<4>(0,1);
        //if (car.dir.y < 0) car.dir.y += FixedNumber16<4>(0,1);
        //printf("v0: %f %f\n",car.vel.x.asFloat(), car.vel.y.asFloat());
        //printf("d0: %f %f\n",car.dir.x.asFloat(), car.dir.y.asFloat());
        car.vel.scale((propFront.friction + propBack.friction) * FixedNumber16<4>(0,8));
        //printf("v1: %f %f\n",car.vel.x.asFloat(), car.vel.y.asFloat());
        //printf("d1: %f %f\n",car.dir.x.asFloat(), car.dir.y.asFloat());
        car.vel+=car.dir * len * FixedNumber16<4>(2,0);
        if (car.vel.x < 0) car.vel.x+=FixedNumber16<4>(0,1);
        if (car.vel.y < 0) car.vel.y+=FixedNumber16<4>(0,1);
        if (car.vel.x > 0) car.vel.x-=FixedNumber16<4>(0,1);
        if (car.vel.y > 0) car.vel.y-=FixedNumber16<4>(0,1);
        //printf("%d %d\n",car.vel.x.getFractionPart(),car.vel.y.getFractionPart());


        car.pos += car.vel;
        int groundTypeFrontFuture = Map::getGroundType(car.pos.x.getIntegerPart() + (car.dir.x * 4).getIntegerPart(), car.pos.y.getIntegerPart() + (car.dir.y * 4).getIntegerPart());
        int groundTypeBackFuture = Map::getGroundType(car.pos.x.getIntegerPart() - (car.dir.x * 4).getIntegerPart(), car.pos.y.getIntegerPart() - (car.dir.y * 4).getIntegerPart());
        if (groundProperties[groundTypeFrontFuture].solid || groundProperties[groundTypeFrontFuture].solid) {
            car.pos -= car.vel;
            car.vel.scale(FixedNumber16<4>(0,12));
        }

        //printf("%d \n",groundType);

        if (car.pos.x < FixedNumber16<4>(96+32,0)) car.pos.x = FixedNumber16<4>(96+32,0);
        if (car.pos.y < FixedNumber16<4>(64+32,0)) car.pos.y = FixedNumber16<4>(64+32,0);
        if (car.pos.x > FixedNumber16<4>(Map::getWidth()-32,0)) car.pos.x = FixedNumber16<4>(Map::getWidth()-32,0);
        if (car.pos.y > FixedNumber16<4>(Map::getHeight()-32,0)) car.pos.y = FixedNumber16<4>(Map::getHeight()-32,0);
        Camera::setPosition(car.pos + car.vel * 5 + car.dir * 3);
        //printf(" %f %f\n",car.vel.length().asFloat(), len.asFloat());
        if (tickCounter%2 == 0) {
            uint32_t rx = Math::randInt();
            uint32_t ry = Math::randInt();
            Fixed2D4 moveDir = car.vel;
            moveDir.normalize();
            Particle::spawn(car.pos - moveDir * FixedNumber16<4>(6,0),
                            car.vel * FixedNumber16<4>(0,12) + Fixed2D4(FixedNumber16<4>(0,(rx%5)), FixedNumber16<4>(0,ry%5)).scale(FixedNumber16<4>(rx & 256 ? 1 : -1,0)),
                            car.groundType.particleType,
                            (car.vel.length() * FixedNumber16<4>(6,0)).getIntegerPart() + 1);
        }
    }
    void init() {
        car.pos.x.setIntegerPart(400);
        car.pos.y.setIntegerPart(400);
        car.dir.x.setIntegerPart(1);

        groundProperties[Map::GroundType::forrest].init(2,0, true);
        groundProperties[Map::GroundType::ground].init(9,3, false);
        groundProperties[Map::GroundType::road].init(13,0, false);
        groundProperties[Map::GroundType::sandpit].init(8,2, false);
        groundProperties[Map::GroundType::water].init(3,1,false);
    }
}
