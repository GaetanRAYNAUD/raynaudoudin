#include "State.h"
#include "TeamId.h"

namespace state {

    State::State(int width, int height) {
        board = Board(width, height);
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
    
    const TeamId State::getCurrentTeam() const {
        switch (turn % 2) {
            case 0:
                return TeamId::TEAM_1;
                break;
            case 1:
                return TeamId::TEAM_2;
                break;
            default:
                return TeamId::INVALIDTEAM;
        }
    }

    void State::endTurn() {
        board.endTurn(getCurrentTeam());
        turn = turn + 1;
    }


    void State::setTurn(int turn) {
        this->turn = turn;
    }
    
    void State::setEpoch(int epoch) {
        this->epoch = epoch;
    }

    TeamId State::getWinner() const {
        return winner;
    }

    void State::setWinner(TeamId winner) {
        this->winner = winner;
    }
}