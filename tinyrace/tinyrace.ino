
#include <SPI.h>
#include <Wire.h>

#include <string.h>
#include "game_core.h"
#include "game_camera.h"
#include "game_car.h"
#include "game_map.h"


void setup() {
    Wire.begin();
    display.begin();

    display.setFlip(0);
    display.setBrightness(8);
    display.setBitDepth(buffer.is16bit());
    buffer.setClearBackground(true,RGB565(200,205,220));

    Car::init();
    Map::init();
}


void loop() {
    static uint32_t t = 0;
    Joystick::updateJoystick();
    Time::millis = millis();
    uint32_t dt = Time::millis - t;

    Car::tick();
    Camera::tick();
    Map::tick();

    Camera::draw();
    Car::draw();
    Map::draw();

    //drawTextBubble("Here we are.\nQ: (3+2)*4=__",1,6,10,2, 5,0);
    buffer.flush(display);
    stringBuffer.reset();

    while (millis() - Time::millis < 33)
    {

    }
    t = Time::millis;
}