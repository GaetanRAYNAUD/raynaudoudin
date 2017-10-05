#include "Wall.h"

namespace state {

    Wall::Wall(int id, int positionX, int positionY) {
        this->id = id;
        this->positionX = positionX;
        this->positionY = positionY;
        this->typeId = TerrainTypeId::WALL;
    }

    Orientation Wall::getOrientation() const {
        return orientation;
    }

    void Wall::setOrientation(Orientation orientation) {
        this->orientation = orientation;
    }

    Terrain* Wall::clone() const {
        return new Wall(*this);
    }
    
}