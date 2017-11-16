#include "StateLayer.h"
#include "MenuTileSet.h"

namespace render {

    StateLayer::StateLayer(const state::State& state): state(state) {
        tileset = std::make_shared<MenuTileSet>();
    }

    void StateLayer::initSurface() {
        Tile tileMenuTop, tileMenuLeft;
        
        surface->loadTexture(tileset->getImageFile());
        surface->initQuads(2);
        
        tileMenuTop = tileset->getTile(MenuTypeId::MENU_TOP);
        
        surface->setSpriteTexture(0, tileMenuTop);
        surface->setSpriteLocation(0, 0, 0, 1920, tileMenuTop.getHeight());
        
        tileMenuLeft = tileset->getTile(MenuTypeId::MENU_LEFT);
        
        surface->setSpriteTexture(1, tileMenuLeft);
        surface->setSpriteLocation(1, 0, tileMenuTop.getHeight(), 72 / 4, 1080);
    }

    void StateLayer::stateChanged(const state::Event& event) {

    }


}
