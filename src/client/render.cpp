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

bool render::loadTerrain(const std::string& tilepath, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height) {
    // on charge la texture du tileset
    if (!textureTerrain.loadFromFile(tilepath))
        return false;

    // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
    vertexTerrain.setPrimitiveType(sf::Quads);
    vertexTerrain.resize(width * height * 4);

    // on remplit le tableau de vertex, avec un quad par tuile
    for (unsigned int i = 0; i < width; ++i)
        for (unsigned int j = 0; j < height; ++j)
        {
            // on récupère le numéro de tuile courant
            int tileNumber = tiles[i + j * width];

            // on en déduit sa position dans la texture du tileset
            int tu = tileNumber % (textureTerrain.getSize().x / tileSize.x);
            int tv = tileNumber / (textureTerrain.getSize().x / tileSize.x);

            // on récupère un pointeur vers le quad à définir dans le tableau de vertex
            sf::Vertex* quadTerrain = &vertexTerrain[(i + j * width) * 4];

            // on définit ses quatre coins
            if (i % 2) {
                quadTerrain[0].position = sf::Vector2f(i * tileSize.x - i * tileSize.x / 4, j * tileSize.y);
                quadTerrain[1].position = sf::Vector2f((i + 1) * tileSize.x - i * tileSize.x / 4, j * tileSize.y);
                quadTerrain[2].position = sf::Vector2f((i + 1) * tileSize.x - i * tileSize.x / 4, (j + 1) * tileSize.y);
                quadTerrain[3].position = sf::Vector2f(i * tileSize.x - i * tileSize.x / 4, (j + 1) * tileSize.y);
            }
            else {
                quadTerrain[0].position = sf::Vector2f(i * tileSize.x - i * tileSize.x / 4, j * tileSize.y + tileSize.y / 2);
                quadTerrain[1].position = sf::Vector2f((i + 1) * tileSize.x - i * tileSize.x / 4, j * tileSize.y + tileSize.y / 2);
                quadTerrain[2].position = sf::Vector2f((i + 1) * tileSize.x - i * tileSize.x / 4, (j + 1) * tileSize.y + tileSize.y / 2);
                quadTerrain[3].position = sf::Vector2f(i * tileSize.x - i * tileSize.x / 4, (j + 1) * tileSize.y + tileSize.y / 2);
            }
                // on définit ses quatre coordonnées de texture
                quadTerrain[0].texCoords = sf::Vector2f(tu * tileSize.x , tv * tileSize.y);
                quadTerrain[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                quadTerrain[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                quadTerrain[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }
    
    return true;
}

bool render::loadMenu(const std::string& menuTilepath, int  windowWidth, int windowHeight) {
    if (!textureMenu.loadFromFile(menuTilepath))
        return false;

    sf::Vector2u topMenuSize = sf::Vector2u(833, 36);
    sf::Vector2u leftMenuSize = sf::Vector2u(58, 700);
    vertexMenu.setPrimitiveType(sf::Quads);
    vertexMenu.resize(2 * 4);
    
    //init menuTop
    sf::Vertex* quadMenu = &vertexMenu[0];
    quadMenu[0].position = sf::Vector2f(0, 0);
    quadMenu[1].position = sf::Vector2f(windowWidth, 0);
    quadMenu[2].position = sf::Vector2f(windowWidth, topMenuSize.y);
    quadMenu[3].position = sf::Vector2f(0, topMenuSize.y);
    
    quadMenu[0].texCoords = sf::Vector2f(0, 0);
    quadMenu[1].texCoords = sf::Vector2f(topMenuSize.x, 0);
    quadMenu[2].texCoords = sf::Vector2f(topMenuSize.x, topMenuSize.y);
    quadMenu[3].texCoords = sf::Vector2f(0, topMenuSize.y);
    
    //init menuLeft
    quadMenu = &vertexMenu[4];
    quadMenu[0].position = sf::Vector2f(0, topMenuSize.y);
    quadMenu[1].position = sf::Vector2f(leftMenuSize.x, topMenuSize.y);
    quadMenu[2].position = sf::Vector2f(leftMenuSize.x, windowHeight);
    quadMenu[3].position = sf::Vector2f(0, windowHeight);
    
    quadMenu[0].texCoords = sf::Vector2f(0, topMenuSize.y + 1);
    quadMenu[1].texCoords = sf::Vector2f(leftMenuSize.x, topMenuSize.y + 1);
    quadMenu[2].texCoords = sf::Vector2f(leftMenuSize.x, topMenuSize.y + leftMenuSize.y);
    quadMenu[3].texCoords = sf::Vector2f(0, topMenuSize.y + leftMenuSize.y);
    
    return true;
}

void render::draw(sf::RenderTarget& target, sf::RenderStates states) const {        
    // on applique la transformation
    states.transform *= getTransform();

    // on applique la texture du tileset
    states.texture = &textureTerrain;

    // et on dessine enfin le tableau de vertex
    target.draw(vertexTerrain, states);
    
    states.texture = &textureMenu;
    target.draw(vertexMenu, states);

}

render::render(const render& orig) {
}

render::~render() {
}

