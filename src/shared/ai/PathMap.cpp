#include <limits>

#include "PathMap.h"

namespace ai {

    int PathMap::getWeight(const Point& p) const {
        return weights[p.getX() + width * (p.getY() / 2)];
    }
    
    void PathMap::setWeight(const Point& p) {
        weights[p.getX() + width * (p.getY() / 2)] = p.getWeight();
    }
    
    std::vector<int> PathMap::getWeights() const {
        return weights;
    }

    void PathMap::init(const state::Board& board) {
        height = board.getHeight();
        width = board.getWidth();
        
        weights.clear();
        weights.resize((height / 2) * width, std::numeric_limits<int>::infinity());
    }

    void PathMap::addWell(Point p) {
        setWeight(p);
        queue.push(p);
    }

    void PathMap::update(const state::Board& board) {
        std::vector<state::Direction> directions;
        
        while (!queue.empty()) {
            Point point = queue.top();
            queue.pop();

            directions = board.directionAvailable(point.getX(), point.getY());
            for (auto d : directions) {
                Point pointTmp = point.transform(d);

                pointTmp.setWeight(point.getWeight() + board.findTerrainOnPosition(pointTmp.getX(), pointTmp.getY())->getMovementCost());
                if (pointTmp.getWeight() < getWeight(pointTmp)) {
                    queue.push(pointTmp);
                    setWeight(pointTmp.getWeight());
                }
            }
        }
    }
    
}
