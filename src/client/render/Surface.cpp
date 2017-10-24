#include "Surface.h"
#include "Tile.h"
#include <iostream>

namespace render {

    void Surface::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        states.texture = &texture;
        target.draw(quads, states);
    }

    void Surface::initQuads(int count) {
        quads.resize(count);
    }

    void Surface::loadTexture(const std::string& image_file) {
        if (!texture.loadFromFile(image_file))
            std::cerr << "Impossible de charger la texture : " << image_file << std::endl;
    }

    void Surface::setSpriteLocation(int i, int x, int y, int width, int height) {
        quads[i * 4].position = sf::Vector2f(x, y);
        quads[i * 4 + 1].position = sf::Vector2f(x, y);
        quads[i * 4 + 2].position = sf::Vector2f(x + width, y + height);
        quads[i * 4 + 3].position = sf::Vector2f(x, y + height);
    }

    void Surface::setSpriteTexture(int i, const Tile& texture) {
        quads[i * 4].texCoords = sf::Vector2f(texture.getX(), texture.getY());
        quads[i * 4 + 1].texCoords = sf::Vector2f(texture.getX() + texture.getWidth(), texture.getY());
        quads[i * 4 + 2].texCoords = sf::Vector2f(texture.getX() + texture.getWidth(), texture.getY() + texture.getHeight());
        quads[i * 4 + 3].texCoords = sf::Vector2f(texture.getX(), texture.getY() + texture.getHeight());
    }

}