#include "State.h"

namespace state {

    State::State() {
        board = Board(22, 8);
    }
    
    Board& State::getBoard() {
        return board;
    }

}