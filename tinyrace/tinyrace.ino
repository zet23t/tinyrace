
#include <SPI.h>
#include <Wire.h>

#include <string.h>
#include "game_core.h"
#include "game_state.h"

void setup() {
    Wire.begin();
    display.begin();
    analogWrite(A0, analogRead(A0));//Set audio output to avoid picking up noise, even though audio isn't used

    display.setFlip(0);
    display.setBrightness(8);
    display.setBitDepth(buffer.is16bit());
    buffer.setClearBackground(false,RGB565(200,205,220));
    GameState::init();
}


void loop() {
    static uint32_t t = 0;
    Time::millis = millis();

    GameState::tick();
    //drawTextBubble("Here we are.\nQ: (3+2)*4=__",1,6,10,2, 5,0);
    buffer.flush(display);
    stringBuffer.reset();

    while (millis() - Time::millis < 33)
    {

    }
    t = Time::millis;
}
