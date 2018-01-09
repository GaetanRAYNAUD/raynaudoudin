#include "Surface.h"
#include "Tile.h"
#include <iostream>

namespace render {

    void Surface::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        states.texture = &texture;
        target.draw(quads, states);
        
        for(auto& t : texts) {
            target.draw(t, states);
        }
    }

    void Surface::initQuads(int count) {
        quads.setPrimitiveType(sf::Quads);
        quads.resize(count * 4);
    }

    void Surface::loadTexture(const std::string& image_file) {
        if (!texture.loadFromFile(image_file))
            std::cerr << "Impossible de charger la texture : " << image_file << std::endl;
    }

    void Surface::setSpriteLocation(int i, int x, int y, int width, int height) {
        quads[i * 4].position = sf::Vector2f(x, y);
        quads[i * 4 + 1].position = sf::Vector2f(x + width, y);
        quads[i * 4 + 2].position = sf::Vector2f(x + width, y + height);
        quads[i * 4 + 3].position = sf::Vector2f(x, y + height);
    }

    void Surface::setSpriteTexture(int i, const Tile& texture) {
        quads[i * 4].texCoords = sf::Vector2f(texture.getX(), texture.getY());
        quads[i * 4 + 1].texCoords = sf::Vector2f(texture.getX() + texture.getWidth(), texture.getY());
        quads[i * 4 + 2].texCoords = sf::Vector2f(texture.getX() + texture.getWidth(), texture.getY() + texture.getHeight());
        quads[i * 4 + 3].texCoords = sf::Vector2f(texture.getX(), texture.getY() + texture.getHeight());
    }

    void Surface::addText(int x, int y, const std::string& msg, sf::Color color, int size) {
        sf::Text text;
        
        if (!font.loadFromFile("res/font/calibri.ttf")) {
            std::cerr << "Unable to load font file" << std::endl;
        }
        
        text.setFont(font);
        text.setString(msg);
        text.setColor(color);
        text.setStyle(sf::Text::Bold);
        text.setCharacterSize(size);
        text.setPosition(x, y);
                       
        texts.push_back(text);
    }
}