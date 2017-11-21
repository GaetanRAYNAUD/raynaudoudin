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

    void PathMap::init(const state::Board& grid) {
        const std::map<int, std::unique_ptr<state::Unit> >& units = grid.getUnits();
        std::vector<state::Direction> directions;
        
        weights.resize(height / 2 * width, std::numeric_limits<int>::infinity());
        
        for (auto& u : units) {
            if (u.second->getTeam() == state::TeamId::TEAM_1) {
                queue.push(Point(u.second->getPositionX(), u.second->getPositionY(), 0));
                while (!queue.empty()) {
                    Point point = queue.top();
                    queue.pop();
                    
                    directions = grid.directionAvailable(point.getX(), point.getY());
                    for (auto d : directions) {
                        Point pointTmp = point.transform(d);
                        
                        pointTmp.setWeight(point.getWeight() + grid.findTerrainOnPosition(pointTmp.getX(), pointTmp.getY())->getMovementCost());
                        if (pointTmp.getWeight() < getWeight(pointTmp)) {
                            queue.push(pointTmp);
                            setWeight(pointTmp.getWeight());
                        }
                    }
                }
            }
        }       
    }

    void PathMap::addWell(Point p) {

    }

    void PathMap::update(const state::Board& grid) {

    }
    
}
