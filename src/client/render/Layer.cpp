#include <iostream>

#include "Layer.h"
#include "TerrainTileSet.h"

namespace render {

    Layer::Layer() : surface(new Surface()) {
    
    }
    
    const Surface* Layer::getSurface() const {
        return surface.get();
    }

    int Layer::getShiftHeight() const {
        return shiftHeight;
    }

    int Layer::getShiftWidth() const {
        return shiftWidth;
    }
    
    void Layer::setSurface(Surface* surface) {
        this->surface = std::unique_ptr<Surface>(surface);
    }

    void Layer::setShiftHeight(int shiftHeight) {
        this->shiftHeight = shiftHeight;
    }

    void Layer::setShiftWidth(int shiftWidth) {
        this->shiftWidth = shiftWidth;
    }
    
    Layer::~Layer() {

    }
}