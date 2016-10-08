#include "lib_math.h"

#include "game_core.h"
#include "game_car.h"
#include "game_camera.h"

namespace Car {
    struct Car {
        Fixed2D4 pos;
        Fixed2D4 vel;
        Fixed2D4 dir;
    };

    Car car;

    void draw() {
        int x = car.pos.x.getIntegerPart();
        int y = car.pos.y.getIntegerPart();
        int dx = (car.dir.x * FixedNumber16<4>(1,9)).getIntegerPart();
        int dy = (car.dir.y * FixedNumber16<4>(1,9)).getIntegerPart();
        uint16_t col = RGB565(55,10,10);
        buffer.drawRect(x-1,y-1,3,3)->filledRect(col)->setDepth(15);
        buffer.drawRect(x-1+dx,y-1+dy,3,3)->filledRect(col)->setDepth(15);
        buffer.drawRect(x-1-dx,y-1-dy,3,3)->filledRect(col)->setDepth(15);
    }
    void tick() {
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
        FixedNumber16<4> len = stick.length() * FixedNumber16<4>(0,12);
        //stick.normalize();
        car.dir += stick;
        car.dir.normalize();

        car.vel+=car.dir * len;
        car.vel.scale(FixedNumber16<4>(0,15));
        if (car.vel.x < 0) car.vel.x+=FixedNumber16<4>(0,1);
        if (car.vel.y < 0) car.vel.y+=FixedNumber16<4>(0,1);
        if (car.vel.x > 0) car.vel.x-=FixedNumber16<4>(0,1);
        if (car.vel.y > 0) car.vel.y-=FixedNumber16<4>(0,1);
        //printf("%d %d\n",car.vel.x.getFractionPart(),car.vel.y.getFractionPart());
        car.pos += car.vel;
        Camera::setPosition(car.pos + car.vel * 5 + car.dir * 3);
    }
    void init() {
        car.pos.x.setIntegerPart(30);
        car.pos.y.setIntegerPart(30);
        car.dir.x.setIntegerPart(1);
    }
}
