#include "heuristic_ai.hpp"

using namespace state;
using namespace render;
using namespace engine;
using namespace ai;

namespace heuristic_ai {
    
    void heuristic_aiTest() {
        std::priority_queue<Point, std::vector<Point>, PointCompareWeight> queue;
        
        queue.push(Point(0,0,1));
        queue.push(Point(1,1,0));
        queue.push(Point(0,0,0));
        queue.push(Point(2,4,0));
        queue.push(Point(2,8,0));
        queue.push(Point(0,1,0));
        queue.push(Point(1,0,0));
        queue.push(Point(0,0,2));
        queue.push(Point(0,0,4));
        queue.push(Point(0,0,3));
        
        while (!queue.empty()) {
            std::cout << queue.top().getX() << queue.top().getY() << queue.top().getWeight() << std::endl;
            queue.pop();
        }        
    }

}
