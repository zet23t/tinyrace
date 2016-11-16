#include "game_state.h"

#include "game_core.h"
#include "game_camera.h"
#include "game_car.h"
#include "game_map.h"
#include "game_particle.h"
#include "game_menu.h"

namespace GameState {
    void init() {
        Car::init();
        Map::init();
        Particle::init();
        GameMenu::init();

    }
    void tick() {
        Joystick::updateJoystick();

        Car::tick();
        Camera::tick();
        Particle::tick();
        Map::tick();

        Camera::draw();
        Car::draw();
        Particle::draw();
        Map::draw();
    }
}
