#include <limits>

#include "PathMap.h"

namespace ai {

    int PathMap::getWeight(const Point& p) const {
        if (p.getX() >= 0 && p.getY() >= 0 && p.getX() < width && p.getY() < height) {
            return weights[p.getX() + width * (p.getY() / 2)];
        }
        return std::numeric_limits<int>::infinity();
    }   
    
    void PathMap::setWeight(const Point& p) {
        if (p.getX() >= 0 && p.getY() >= 0 && p.getX() < width && p.getY() < height) {
            weights[p.getX() + width * (p.getY() / 2)] = p.getWeight();
        }
    }
    
    const std::vector<int>& PathMap::getWeights() const {
        return weights;
    }
    
    const Point PathMap::getPoint(int x, int y) const {
        if (x >= 0 && y >= 0 && x < width && y < height) {
            int w = getWeight(Point(x, y));
            return Point(x, y, w);
        }
        return Point(x, y, std::numeric_limits<int>::infinity());
    }
    
    const Point PathMap::getBestPoint(int x, int y) const {
        std::priority_queue<Point, std::vector<Point>, PointCompareWeight> points;
        
        points.push(getPoint(x, y - 2));
        points.push(getPoint(x + 1, y - 1));
        points.push(getPoint(x + 1, y + 1));
        points.push(getPoint(x, y + 2));
        points.push(getPoint(x - 1, y + 1));
        points.push(getPoint(x - 1, y - 1));
        
        return points.top();
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
                    setWeight(pointTmp);
                    queue.push(pointTmp);
                }
            }
        }
    }
    
}
