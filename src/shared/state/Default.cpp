#include "Default.h"

namespace state {

    Default::Default(int id, int positionX, int positionY) {
        this->id = id;
        this->positionX = positionX;
        this->positionY = positionY;
        this->typeId = TerrainTypeId::GRASS;
    }
        
    Terrain* Default::clone() const {
        return new Default(*this);
    }

    
}