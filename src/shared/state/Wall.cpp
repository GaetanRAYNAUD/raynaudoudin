#include "Wall.h"

namespace state {

    Wall::Wall(Orientation orientation, int positionX, int positionY) {
        this->id = id;
        this->positionX = positionX;
        this->positionY = positionY;
        
        switch(orientation) {
            case Orientation::RIGHT :
                this->orientation = Orientation::RIGHT;
                this->typeId = TerrainTypeId::WALL_RIGHT;
                break;
            
            case Orientation::LEFT :
                this->orientation = Orientation::LEFT;
                this->typeId = TerrainTypeId::WALL_LEFT;
                break;
                        
            case Orientation::UP :
                this->orientation = Orientation::UP;
                this->typeId = TerrainTypeId::WALL_TOP;
                break;
            
            default :
                this->orientation = Orientation::RIGHT;
                this->typeId = TerrainTypeId::WALL_RIGHT;
                break;                
        }
    }

    const Orientation& Wall::getOrientation() const {
        return orientation;
    }

    void Wall::setOrientation(Orientation orientation) {
        switch(orientation) {
            case Orientation::RIGHT :
                this->orientation = Orientation::RIGHT;
                this->typeId = TerrainTypeId::WALL_RIGHT;
                break;
            
            case Orientation::LEFT :
                this->orientation = Orientation::LEFT;
                this->typeId = TerrainTypeId::WALL_LEFT;
                break;
                        
            case Orientation::UP :
                this->orientation = Orientation::UP;
                this->typeId = TerrainTypeId::WALL_TOP;
                break;
            
            default :
                this->orientation = Orientation::RIGHT;
                this->typeId = TerrainTypeId::WALL_RIGHT;
                break;                
        }
    }

    Terrain* Wall::clone() const {
        return new Wall(*this);
    }

    bool Wall::equals(const Terrain& other) const {
        Wall& otherCompare = (Wall&)other;
        
        if(typeId != otherCompare.typeId) {
            return false;
        }
        
        if(movementCost != otherCompare.movementCost) {
            return false;
        }
        
        if(orientation != otherCompare.orientation) {
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