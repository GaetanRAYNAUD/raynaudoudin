#include "PathMap.h"

namespace ai {

    void PathMap::addSink(Point p) {

    }

    int PathMap::getWeight(const Point& p) const {
        return weights[0];//-Werror
    }

    std::vector<int> PathMap::getWeights() const {
        return weights;
    }

    void PathMap::init(const state::Board& grid) {

    }

    void PathMap::setWeight(const Point& p) {
        
    }

    void PathMap::update(const state::Board& grid) {

    }
    
}
