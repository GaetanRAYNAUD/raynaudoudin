#include <iostream>

#include "Layer.h"
#include "TerrainTileSet.h"

namespace render {

    Layer::Layer() : surface(new Surface()) {
    
    }
    
    const Surface* Layer::getSurface() const {
        return surface.get();
    }

    void Layer::setSurface(Surface* surface) {
        this->surface = std::unique_ptr<Surface>(surface);
    }
    
    Layer::~Layer() {

    }
}