#include "House.h"

namespace state {

    House::House(int positionX, int positionY) {
        this->id = id;
        this->positionX = positionX;
        this->positionY = positionY;
        this->typeId = TerrainTypeId::HOUSE;
        this->movementCost = 1;
        this->teamId = TeamId::INVALIDTEAM;
    }
        
    void House::claim(TeamId teamId) {
        this->teamId = teamId;
    }

    Terrain* House::clone() const {
        return new House(*this);
    }

    const TeamId& House::getTeamId() const {
        return teamId;
    }
    
    
}