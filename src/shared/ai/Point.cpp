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

    int Point::getWeight() const {
        return weight;
    }

    void Point::setX(int x) {
        this->x = x;
    }

    void Point::setY(int y) {
        this->y = y;
    }

    void Point::setWeight(int weight) {
        this->weight = weight;
    }

    Point Point::transformToPoint(state::Direction d) {
        switch (d) {
            case state::Direction::TOP:
                return Point(x, y - 2, weight);
            case state::Direction::TOP_RIGHT:
                return Point(x + 1, y - 1, weight);
            case state::Direction::BOT_RIGHT:
                return Point(x + 1, y + 1, weight);
            case state::Direction::BOT:
                return Point(x, y + 2, weight);
            case state::Direction::BOT_LEFT:
                return Point(x - 1, y + 1, weight);
            case state::Direction::TOP_LEFT:
                return Point(x - 1, y - 1, weight);
            default:
                return Point(x, y, weight);
        }
    }
    
    state::Direction Point::transformToDirection(Point p) {
        if(y == p.getY() - 2) {
            return(state::Direction::TOP);
        } else if(x == p.getX() + 1 && y == p.getY() - 1) {
            return(state::Direction::TOP_RIGHT);
        } else if(x == p.getX() + 1 && y == p.getY() + 1) {
            return(state::Direction::BOT_RIGHT);
        } else if(y == p.getY() + 2) {
            return(state::Direction::BOT);
        } else if(x == p.getX() - 1 && y == p.getY() + 1) {
            return(state::Direction::BOT_LEFT);
        } else if(x == p.getX() - 1 && y == p.getY() - 1) {
            return(state::Direction::TOP_LEFT);
        } else {
            return state::Direction::BOT;
        }
    }
    
}
