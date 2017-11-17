#include "StateLayer.h"
#include "MenuTileSet.h"

namespace render {

    StateLayer::StateLayer(const state::State& state): state(state) {
        tileset = std::make_shared<MenuTileSet>();
    }

    void StateLayer::initSurface() {
        Tile tileMenuTop, tileMenuLeft, tileGold, tileHouse;
        
        surface->loadTexture(tileset->getImageFile());
        surface->initQuads(4);
        
        tileMenuTop = tileset->getTile(MenuTypeId::MENU_TOP);
        
        surface->setSpriteTexture(0, tileMenuTop);
        surface->setSpriteLocation(0, 0, 0, 1920, tileMenuTop.getHeight());
        
        tileMenuLeft = tileset->getTile(MenuTypeId::MENU_LEFT);
        
        surface->setSpriteTexture(1, tileMenuLeft);
        surface->setSpriteLocation(1, 0, tileMenuTop.getHeight(), 72 / 4, 1080);
        
        tileGold = tileset->getTile(MenuTypeId::MENU_GOLD);
        
        surface->setSpriteTexture(2, tileGold);
        surface->setSpriteLocation(2, 18, 12, 16, 16);
        
        tileHouse = tileset->getTile(MenuTypeId::MENU_HOUSE);
        
        surface->setSpriteTexture(3, tileHouse);
        surface->setSpriteLocation(3, 100, 12, 16, 16);      
        
        surface->addText(34, 12, std::to_string(state.getBoard().findTeam(state.getCurrentTeam())->getGold()));        
    }

    void StateLayer::stateChanged(const state::Event& event) {

    }


}
