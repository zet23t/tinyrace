#include "game_state.h"

#include "game_core.h"
#include "game_camera.h"
#include "game_car.h"
#include "game_map.h"
#include "game_particle.h"
#include "game_menu.h"

namespace GameState {
    namespace Mode {
        const uint8_t MainMenu = 1;
        const uint8_t Race = 2;
    }

    static uint8_t CurrentMode;

    void init() {
        CurrentMode = Mode::MainMenu;

        Car::init();
        Map::init();
        Particle::init();
        GameMenu::init();

    }

    void tickMainMenu() {
        GameMenu::tick();
        GameMenu::draw();
    }

    void tickRace() {
        Car::tick();
        Camera::tick();
        Particle::tick();
        Map::tick();

        Camera::draw();
        Car::draw();
        Particle::draw();
        Map::draw();
    }
    void tick() {
        Joystick::updateJoystick();
        switch (CurrentMode) {
            default: tickMainMenu(); break;
            case Mode::Race: tickRace(); break;
        }

    }
    void setMode(uint8_t mode) {
        CurrentMode = mode;
    }
}
