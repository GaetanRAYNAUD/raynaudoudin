#include "Terrain.h"

namespace state {

    Terrain::Terrain() {

    }

    int Terrain::getId() const {
        return id;
    }

    int Terrain::getMovementCost() const {
        return movementCost;
    }

    int Terrain::getPositionX() const {
        return positionX;
    }

    int Terrain::getPositionY() const {
        return positionY;
    }

    TerrainTypeId Terrain::getTypeId() const {
        return typeId;
    }

    void Terrain::setId(int id) {
        this->id = id;
    }

    void Terrain::setMovementCost(int movementCost) {
        this->movementCost = id;
    }

    void Terrain::setPositionX(int positionX) {
        this->positionX = positionX;
    }

    void Terrain::setPositionY(int positionY) {
        this->positionY = positionY;
    }

    void Terrain::setTypeId(TerrainTypeId typeId) {
        this->typeId = typeId;
    }

    Terrain::~Terrain() {
        
    }


    
}