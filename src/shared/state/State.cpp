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

    int State::getEpoch() const {
        return epoch;
    }

    void State::setTurn(int turn) {
        this->turn = turn;
    }
    
    void State::setEpoch(int epoch) {
        this->epoch = epoch;
    }
    
}