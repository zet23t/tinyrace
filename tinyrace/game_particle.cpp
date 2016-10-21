#include "game_core.h"
#include "game_particle.h"
#include "image_data.h"

namespace Particle {

    Texture<uint16_t> atlas;
    const SpriteSheet *particleSheets[4];

    struct Particle {
        uint16_t age, maxAge;
        Fixed2D4 pos, vel;
        uint8_t type;

        bool isActive() const {
            return age < maxAge;
        }
        void initialize(Fixed2D4 pos, Fixed2D4 vel, uint8_t type, uint16_t maxAge) {
            this->pos = pos;
            this->vel = vel;
            this->type = type;
            this->maxAge = maxAge;
            this->age = 0;
        }

        void draw() {
            if (age < maxAge) {
                int x = this->pos.x.getIntegerPart();
                int y = this->pos.y.getIntegerPart();
                const SpriteSheet *sheet = particleSheets[type];
                int spriteIndex = age * sheet->spriteCount / maxAge;
                SpriteSheetRect rect = sheet->sprites[spriteIndex];
                int w = rect.width, h = rect.height;
                buffer.drawRect(x - w / 2,y - h / 2,w,h)->sprite(&atlas,rect.x,rect.y)->setDepth(25 + age);
            }
        }
        void tick() {
            if (age < maxAge) {
                this->pos += this->vel;
                this->age += 1;
            }
        }
    };

    Particle particles[MAX_PARTICLES];

    void init() {
        atlas = Texture<uint16_t>(ImageAsset::atlas);
        particleSheets[0]= &ImageAsset::TextureAtlas_atlas::particle;
        particleSheets[1]= &ImageAsset::TextureAtlas_atlas::splash;
        particleSheets[2]= &ImageAsset::TextureAtlas_atlas::sandparticles;
        particleSheets[3]= &ImageAsset::TextureAtlas_atlas::grassparticles;
    }

    void spawn (Fixed2D4 pos, Fixed2D4 vel, uint8_t type, uint16_t maxAge) {
        for (int i=0;i<MAX_PARTICLES;i+=1) {
            if (!particles[i].isActive()) {
                particles[i].initialize(pos,vel,type,maxAge);
                return;
            }
        }
    }

    void tick() {
        for (int i=0;i<MAX_PARTICLES;i+=1) {
            particles[i].tick();
        }
    }

    void draw() {
        for (int i=0;i<MAX_PARTICLES;i+=1) {
            particles[i].draw();
        }
    }

}
