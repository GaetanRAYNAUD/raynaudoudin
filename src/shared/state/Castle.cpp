#include "Castle.h"

namespace state {

    Castle::Castle(int id, int positionX, int positionY) {
        this->id = id;
        this->positionX = positionX;
        this->positionY = positionY;
        this->typeId = TerrainTypeId::CASTLE;
    }

    Terrain* Castle::clone() const {
        return new Castle(*this);
    }

    
}