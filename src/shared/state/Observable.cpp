#include <algorithm>

#include "Observable.h"

namespace state {

    void Observable::notifyObservers(const Event& e) const {
        
    }

    void Observable::registerObserver(Observer* o) const {
        observers.push_back(o);
    }

    void Observable::unregisterObserver(Observer* o) const {
        observers.erase(std::remove(observers.begin(), observers.end(), o), observers.end());
    }

    Observable::~Observable() {
        observers.clear();
    }

}
