#include "BoardEvent.h"

namespace state {

    BoardEvent::BoardEvent(int x, int y): x(x), y(y) {

    }

    EventTypeId BoardEvent::getEventType() const {
        return EventTypeId::EVENT_BOARD;
    }
    
}
