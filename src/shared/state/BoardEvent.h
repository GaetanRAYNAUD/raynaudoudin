// Generated by dia2code
#ifndef STATE__BOARDEVENT__H
#define STATE__BOARDEVENT__H


namespace state {
  class Event;
}

#include "EventTypeId.h"
#include "Event.h"

namespace state {

  /// class BoardEvent - 
  class BoardEvent : public state::Event {
    // Attributes
  public:
    int x;
    int y;
    // Operations
  public:
    BoardEvent (int x, int y);
    EventTypeId getEventType () const;
    // Setters and Getters
  };

};

#endif
