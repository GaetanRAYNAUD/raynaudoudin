#include "State.h"

namespace state {

    State::State() {
        board = Board();
    }
    
    Board& State::getBoard() {
        return board;
    }




}