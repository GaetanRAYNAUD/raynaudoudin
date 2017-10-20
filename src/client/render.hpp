/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   render.hpp
 * Author: gaetan
 *
 * Created on 17 octobre 2017, 09:12
 */

#ifndef RENDER_HPP
#define RENDER_HPP

#include <SFML/Graphics.hpp>

class render : public sf::Drawable, public sf::Transformable {
public:
    render();
    bool loadTerrain(const std::string& terrainTilepath, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
    bool loadMenu(const std::string& menuTilepath, int  windowWidth, int windowHeight);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    render(const render& orig);
    virtual ~render();
private:
    sf::VertexArray vertexTerrain;
    sf::Texture textureTerrain;
    sf::VertexArray vertexMenu;
    sf::Texture textureMenu;
};

#endif /* RENDER_HPP */

