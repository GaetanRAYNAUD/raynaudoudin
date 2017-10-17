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
    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    render(const render& orig);
    virtual ~render();
private:
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};

#endif /* RENDER_HPP */

