#include "House.h"

namespace state {

    House::House(int positionX, int positionY) {

    }
        
    void House::claim(int teamId) {

    }

    Terrain* House::clone() const {
        return new House(*this);
    }
    
}