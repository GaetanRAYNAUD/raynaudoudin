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

    void House::setTeamId(TeamId teamId) {
        this->teamId = teamId;
    }
    
    
    bool House::equals(const Terrain& other) const {
        House& otherCompare = (House&)other;
        
        if(typeId != otherCompare.typeId) {
            return false;
        }
        
        if(teamId != otherCompare.teamId) {
            return false;
        }
        
        if(movementCost != otherCompare.movementCost) {
            return false;
        }
        
        if(positionX != otherCompare.positionX) {
            return false;
        }
        
        if(positionY != otherCompare.positionY) {
            return false;
        }
        
        return true;
    }

}