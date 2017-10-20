#include "Layer.h"

namespace render {

    Layer::Layer() {

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