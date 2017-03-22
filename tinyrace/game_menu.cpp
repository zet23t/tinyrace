#include "game_core.h"
#include "game_menu.h"
#include "font_asset.h"
#include "image_data.h"
#include "game_state.h"

namespace GameMenu {
    struct Page;

    int cameraPosition;
    bool armed;

    Page *currentPage;

    struct Page {
        int pageOffset;
        Page *leftPage, *rightPage;
        const SpriteSheetRect *title;// *leftPageName, *rightPageName;
        const char *leftPageName, *rightPageName;
        virtual Page& init() {
            return *this;
        }
        void drawSprite(uint8_t x, uint8_t y, const SpriteSheetRect *rect, int alignmet) {
            if (rect)
                buffer.drawRect(alignmet == -1 ? x : (alignmet == 0 ? x - rect->width / 2 : x - rect->width) ,y,rect->width, rect->height)->sprite(&textureAtlas,rect->x,rect->y);
        }
        virtual void OnRightPage() {
        }
        void draw() {
            buffer.setOffset(-pageOffset + cameraPosition,0);
            buffer.drawRect(0,0,96,17)->filledRect(RGB565(255,128,0));
            buffer.drawRect(0,17,96,1)->filledRect(RGB565(255,255,255));
            buffer.drawRect(0,18,96,64)->filledRect(RGB565(64,128,255));
            drawSprite(48,2,title, 0);
            const int vpos = 50;
            buffer.drawRect(0,vpos-2,96,1)->filledRect(RGB565(255,255,255));
            //drawSprite(13,44,leftPageName,-1);
            //drawSprite(80,26,rightPageName,1);
            if (rightPageName) buffer.drawText(rightPageName,0,vpos,86,16,1,0,false, FontAsset::font2, 4);
            if (leftPageName) buffer.drawText(leftPageName,11,vpos,80,16,-1,0,false, FontAsset::font2, 4);
            if (leftPage) {
                drawSprite(10,vpos+3,&ImageAsset::TextureAtlas_atlas::arrow.sprites[4],1);
            }
            if (rightPage) {
                drawSprite(86,vpos+3,&ImageAsset::TextureAtlas_atlas::arrow.sprites[12],-1);
                //drawSprite(83,vpos,ImageAsset::TextureAtlas_atlas::menu_arrow_right.sprites, -1);
            }

        }
        void tick() {
            FixedNumber16<4> x = Joystick::getJoystick().x;
            if (leftPage && armed && x < FixedNumber16<4>(-1,12)) {
                armed = false;
                currentPage = leftPage;
            }
            if (rightPage && armed && x > FixedNumber16<4>(0,4)) {
                armed = false;
                currentPage = rightPage;
            }
            if (!rightPage && armed && x > FixedNumber16<4>(0,4)) {
                armed = false;
                OnRightPage();
            }


            if (x > FixedNumber16<4>(-1,14) && x < FixedNumber16<4>(0,2)) {
                armed = true;
            }
        }

        Page& setLeftPage(Page* p) {
            leftPage = p;
            if (p) {
                p->rightPage = this;
                p->pageOffset = pageOffset - 96;
            }
            return *this;
        }

        Page& setRightPage(Page *p) {
            rightPage = p;
            if (p) {
                p->leftPage = this;
                p->pageOffset = pageOffset + 96;
            }
            return *this;
        }
    };

    struct MainPage : public Page {
        virtual Page& init() {
            title = ImageAsset::TextureAtlas_atlas::logo.sprites;
            leftPageName = "Credits"; //ImageAsset::TextureAtlas_atlas::menu_credits.sprites;
            rightPageName = "Car"; //ImageAsset::TextureAtlas_atlas::menu_play.sprites;
            return *this;
        }
    };

    struct CreditsPage : public Page {
        virtual Page& init() {
            title = ImageAsset::TextureAtlas_atlas::menu_title_credits.sprites;
            //leftPageName = ImageAsset::TextureAtlas_atlas::menu_credits.sprites;
            //rightPageName = ImageAsset::TextureAtlas_atlas::menu_play.sprites;
            return *this;
        }
    };

    struct MapPage : public Page {
        virtual Page& init() {
            title = ImageAsset::TextureAtlas_atlas::menu_title_map.sprites;
            //leftPageName = ImageAsset::TextureAtlas_atlas::menu_credits.sprites;
            rightPageName = "Start";//ImageAsset::TextureAtlas_atlas::menu_start.sprites;
            leftPageName = "Back";
            return *this;
        }
        virtual void OnRightPage() {
            GameState::setMode(GameState::Mode::Race);
        }
    };

    struct CarPage : public Page {
        virtual Page& init() {
            title = ImageAsset::TextureAtlas_atlas::menu_title_map.sprites;
            //leftPageName = ImageAsset::TextureAtlas_atlas::menu_credits.sprites;
            rightPageName = "Map";//ImageAsset::TextureAtlas_atlas::menu_start.sprites;
            leftPageName = "Back";
            return *this;
        }
    };




    MainPage mainPage;
    CreditsPage creditsPage;
    MapPage mapPage;
    CarPage carPage;

    void init() {
        mainPage.init().setLeftPage(&creditsPage).setRightPage(&carPage);
        carPage.init().setRightPage(&mapPage);
        mapPage.init();
        creditsPage.init();
        currentPage = &mainPage;
    }
    void tick() {
        currentPage->tick();
    }
    void draw() {
        cameraPosition = cameraPosition * 2 / 3 + currentPage->pageOffset / 3;
        if (cameraPosition < currentPage->pageOffset) cameraPosition += 1;
        if (cameraPosition > currentPage->pageOffset) cameraPosition -= 1;
        currentPage->draw();
        if (currentPage->rightPage) {
            currentPage->rightPage->draw();
        }
        if (currentPage->leftPage) {
            currentPage->leftPage->draw();
        }
        //buffer.drawRect(0,0,96,64)->filledRect(RGB565(255,128,0));

        //buffer.drawText("ABCDEFGHIJKL MNOPQRSTUVWXYZ abcdefghijkl mnopqrstuvwxyz 0123456789 .:,;-+=",0,20,96,16,0,0,true, FontAsset::font2, 4);
    }
}
