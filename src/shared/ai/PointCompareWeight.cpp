#include "PointCompareWeight.h"

namespace ai {

    bool PointCompareWeight::operator()(const Point& a, const Point& b) {
        return a.getWeight() < b.getWeight();
    }
    
}
