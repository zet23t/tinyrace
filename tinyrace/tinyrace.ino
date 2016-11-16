
#include <SPI.h>
#include <Wire.h>

#include <string.h>
#include "game_core.h"
#include "game_camera.h"
#include "game_car.h"
#include "game_map.h"
#include "game_particle.h"


void setup() {
    Wire.begin();
    display.begin();
    analogWrite(A0, analogRead(A0));//Set audio output to avoid picking up noise, even though audio isn't used

    display.setFlip(0);
    display.setBrightness(8);
    display.setBitDepth(buffer.is16bit());
    buffer.setClearBackground(true,RGB565(200,205,220));

    Car::init();
    Map::init();
    Particle::init();
}


void loop() {
    static uint32_t t = 0;
    Joystick::updateJoystick();
    Time::millis = millis();
    uint32_t dt = Time::millis - t;

    Car::tick();
    Camera::tick();
    Particle::tick();
    Map::tick();

    Camera::draw();
    Car::draw();
    Particle::draw();
    Map::draw();

    //drawTextBubble("Here we are.\nQ: (3+2)*4=__",1,6,10,2, 5,0);
    buffer.flush(display);
    stringBuffer.reset();

    while (millis() - Time::millis < 33)
    {

    }
    t = Time::millis;
}
