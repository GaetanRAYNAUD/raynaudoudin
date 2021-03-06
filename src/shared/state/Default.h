// Generated by dia2code
#ifndef STATE__DEFAULT__H
#define STATE__DEFAULT__H


namespace state {
  class Terrain;
}

#include "TerrainTypeId.h"
#include "Terrain.h"

namespace state {

  /// class Default - 
  class Default : public state::Terrain {
    // Operations
  public:
    Default (TerrainTypeId typeId, int movementCost, int positionX = 10, int positionY = 10);
    Terrain* clone () const;
    // Setters and Getters
  };

};

#endif
