/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   render.cpp
 * Author: gaetan
 * 
 * Created on 17 octobre 2017, 09:12
 */

#include "render.hpp"

render::render() {
    
}

bool render::load(const std::string& tilepath, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height) {
    // on charge la texture du tileset
    if (!m_tileset.loadFromFile(tilepath))
        return false;

    // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);

    // on remplit le tableau de vertex, avec un quad par tuile
    for (unsigned int i = 0; i < width; ++i)
        for (unsigned int j = 0; j < height; ++j)
        {
            // on récupère le numéro de tuile courant
            int tileNumber = tiles[i + j * width];

            // on en déduit sa position dans la texture du tileset
            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            // on récupère un pointeur vers le quad à définir dans le tableau de vertex
            sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

            // on définit ses quatre coins
            if (i % 2) {
                quad[0].position = sf::Vector2f(i * tileSize.x - i * tileSize.x / 4, j * tileSize.y);
                quad[1].position = sf::Vector2f((i + 1) * tileSize.x - i * tileSize.x / 4, j * tileSize.y);
                quad[2].position = sf::Vector2f((i + 1) * tileSize.x - i * tileSize.x / 4, (j + 1) * tileSize.y);
                quad[3].position = sf::Vector2f(i * tileSize.x - i * tileSize.x / 4, (j + 1) * tileSize.y);
            }
            else {
                quad[0].position = sf::Vector2f(i * tileSize.x - i * tileSize.x / 4, j * tileSize.y + tileSize.y / 2);
                quad[1].position = sf::Vector2f((i + 1) * tileSize.x - i * tileSize.x / 4, j * tileSize.y + tileSize.y / 2);
                quad[2].position = sf::Vector2f((i + 1) * tileSize.x - i * tileSize.x / 4, (j + 1) * tileSize.y + tileSize.y / 2);
                quad[3].position = sf::Vector2f(i * tileSize.x - i * tileSize.x / 4, (j + 1) * tileSize.y + tileSize.y / 2);
            }
                // on définit ses quatre coordonnées de texture
                quad[0].texCoords = sf::Vector2f(tu * tileSize.x , tv * tileSize.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }

    return true;
}

void render::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // on applique la transformation
    states.transform *= getTransform();

    // on applique la texture du tileset
    states.texture = &m_tileset;

    // et on dessine enfin le tableau de vertex
    target.draw(m_vertices, states);
}

render::render(const render& orig) {
}

render::~render() {
}

