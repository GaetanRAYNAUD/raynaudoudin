#include "MenuLayer.h"
#include "MenuTileSet.h"

namespace render {

    MenuLayer::MenuLayer() {
        tileset = std::make_shared<MenuTileSet>();    
    }

    void MenuLayer::initSurface() {
        Tile tile = tileset->getTile();
        
        surface->addText(550, 260, "Jouer", sf::Color::Red, 25);
        
        surface->loadTexture(tileset->getImageFile());
        surface->initQuads(1);
        
        surface->setSpriteTexture(0, tile);
        surface->setSpriteLocation(0, 0, 0, tile.getWidth(), tile.getHeight());       
    }

}

