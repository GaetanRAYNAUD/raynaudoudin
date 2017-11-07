#include <iostream>

#include "Layer.h"
#include "TerrainTileSet.h"

namespace render {

    Layer::Layer() : surface(new Surface()) {
    
    }
    
    const Surface* Layer::getSurface() const {
        return surface.get();
    }

    void Layer::setSurface(Surface* surface) {
        this->surface = std::unique_ptr<Surface>(surface);
    }
    
    Layer::~Layer() {

    }

    void Layer::printText(int x, int y, const std::string& msg, int size, const sf::Color color) {
        sf::Text text;
        sf::Font font;
        
        if (!font.loadFromFile("res/font/calibri.ttf")) {
            std::cerr << "Unable to load font file" << std::endl;
        }
        
        text.setFont(font);
        text.setString(msg);
        text.setColor(color);
        text.setCharacterSize(size);
        text.setPosition(x, y);
    }

}