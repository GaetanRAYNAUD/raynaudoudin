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
                        
            case Orientation::TOP :
                this->orientation = Orientation::TOP;
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
                        
            case Orientation::TOP :
                this->orientation = Orientation::TOP;
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
    
}