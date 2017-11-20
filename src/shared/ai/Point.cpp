#include "Point.h"

namespace ai {

    Point::Point(int x, int y, int weight): x(x), y(y), weight(weight) {

    }

    int Point::getX() const {
        return x;
    }

    int Point::getY() const {
        return y;
    }

    void Point::setX(int x) {
        this->x = x;
    }

    void Point::setY(int y) {
        this->y = y;
    }

    Point Point::transform(state::Direction d) {
        return Point();//-Werror
    }
    
}
