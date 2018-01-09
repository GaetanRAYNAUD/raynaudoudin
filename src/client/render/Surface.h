// Generated by dia2code
#ifndef RENDER__SURFACE__H
#define RENDER__SURFACE__H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

namespace sf {
  class Texture;
  class VertexArray;
};
namespace render {
  class Tile;
};
namespace sf {
  class Drawable;
  class Transformable;
}


namespace render {

  /// class Surface - 
  class Surface : public sf::Drawable, public sf::Transformable {
    // Attributes
  private:
    sf::Texture texture;
    sf::VertexArray quads;
    std::vector<sf::Text> texts;
    sf::Font font;
    // Operations
  public:
    void loadTexture (const std::string& image_file);
    void initQuads (int count);
    void setSpriteLocation (int i, int x, int y, int width, int height);
    void setSpriteTexture (int i, const Tile& texture);
    /// 											
    /// @param target		(???) 
    /// @param states		(???) 
    void draw (sf::RenderTarget& target, sf::RenderStates states) const;
    void addText (int x, int y, const std::string& msg, sf::Color color, int size = 14);
    // Setters and Getters
  };

};

#endif
