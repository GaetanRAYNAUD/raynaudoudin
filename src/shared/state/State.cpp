#include "State.h"

namespace state {

    State::State() {
        board = Board(22, 8);
    }
    
    Board& State::getBoard() {
        return board;
    }
    
    const Board& State::getBoard() const {
        return board;
    }    
    
    int State::getTurn() const {
        return turn;
    }
    
    void State::nextTurn() {
        turn = turn + 1;
    }

}