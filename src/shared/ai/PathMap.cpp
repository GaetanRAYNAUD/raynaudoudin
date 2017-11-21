#include "PathMap.h"

namespace ai {

    int PathMap::getWeight(const Point& p) const {
        return weights[0];//-Werror
    }
    
    void PathMap::setWeight(const Point& p) {

    }
    
    std::vector<int> PathMap::getWeights() const {
        return weights;
    }

    void PathMap::init(const state::Board& grid) {
//        const std::map<int, std::unique_ptr<state::Terrain> >& terrains;
//        
//        for (auto& t : terrains) {
//            
//        }
    }

    void PathMap::addSink(Point p) {

    }

    void PathMap::update(const state::Board& grid) {

    }
    
}
