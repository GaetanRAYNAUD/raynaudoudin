// Generated by dia2code
#ifndef RENDER__TILESET__H
#define RENDER__TILESET__H

#include <string>

namespace render {
  class Tile;
};
namespace state {
  class Terrain;
  class Unit;
}

#include "MenuTypeId.h"
#include "state/Terrain.h"
#include "state/Unit.h"
#include "Tile.h"

namespace render {

  /// class TileSet - 
  class TileSet {
    // Associations
    // Operations
  public:
    virtual ~TileSet ();
    virtual int getCellWidth () const = 0;
    virtual int getCellHeight () const = 0;
    virtual const std::string getImageFile () const = 0;
    const Tile& getTile () const;
    virtual const Tile& getTile (MenuTypeId menu) const;
    virtual const Tile& getTile (const state::Terrain& terrain) const;
    virtual const Tile& getTile (const state::Unit& unit) const;
    // Setters and Getters
  };

};

#endif
