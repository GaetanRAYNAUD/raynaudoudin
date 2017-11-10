#include "Default.h"

namespace state {

    Default::Default(TerrainTypeId typeId, int movementCost, int positionX, int positionY) {
        this->id = id;
        this->positionX = positionX;
        this->positionY = positionY;
        this->typeId = typeId;
        this->movementCost = movementCost;
    }
        
    Terrain* Default::clone() const {
        return new Default(*this);
    }

    
}