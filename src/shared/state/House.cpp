#include "House.h"

namespace state {

    House::House(int id, int positionX, int positionY) {
        this->id = id;
        this->positionX = positionX;
        this->positionY = positionY;
        this->typeId = TerrainTypeId::HOUSE;
    }
        
    void House::claim(int teamId) {
        this->teamId = teamId;
    }

    Terrain* House::clone() const {
        return new House(*this);
    }
    
}