// Generated by dia2code
#ifndef RENDER__SCENE__H
#define RENDER__SCENE__H

#include <SFML/Graphics.hpp>

namespace state {
  class State;
};
namespace render {
  class TerrainLayer;
  class UnitLayer;
  class StateLayer;
};
namespace sf {
  class RenderWindow;
};
namespace state {
  class Observer;
}

#include "TerrainLayer.h"
#include "UnitLayer.h"
#include "StateLayer.h"
#include "state/Observer.h"

namespace render {

  /// class Scene - 
  class Scene {
    // Associations
    // Attributes
  public:
    int shiftWidth;
    int shiftHeight;
  private:
    const state::State& state;
    int width     = 0;
    int heigh     = 0;
    TerrainLayer terrainLayer;
    UnitLayer unitLayer;
    StateLayer stateLayer;
    // Operations
  public:
    Scene (const state::State& state);
    int getWidth () const;
    int getHeigh () const;
    int getShiftWidth () const;
    int getShiftHeight () const;
    void setShiftWidth (int shiftWidth);
    void setShiftHeight (int shiftHeight);
    void stateChanged (const state::Event& event);
    void draw (sf::RenderWindow& window);
    // Setters and Getters
  };

};

#endif
