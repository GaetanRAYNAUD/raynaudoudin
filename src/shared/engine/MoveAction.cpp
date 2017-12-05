#include "MoveAction.h"
#include "state/State.h"

namespace engine {

    MoveAction::MoveAction(int idUnit, state::Direction direction) : idUnit(idUnit), direction(direction) {

    }

    void MoveAction::apply(state::State& state) {
           state.getBoard().moveUnit(idUnit, direction);
    }

    void MoveAction::undo(state::State& state) {
        switch (direction) {
            case state::Direction::TOP:
                state.getBoard().moveUnit(idUnit, state::Direction::BOT);                
                break;
            case state::Direction::TOP_RIGHT:
                state.getBoard().moveUnit(idUnit, state::Direction::BOT_LEFT);                  
                break;
            case state::Direction::BOT_RIGHT:
                state.getBoard().moveUnit(idUnit, state::Direction::TOP_LEFT);                  
                break;
            case state::Direction::BOT:
                state.getBoard().moveUnit(idUnit, state::Direction::TOP);                  
                break;
            case state::Direction::BOT_LEFT:
                state.getBoard().moveUnit(idUnit, state::Direction::TOP_RIGHT);                  
                break;
            case state::Direction::TOP_LEFT:
                state.getBoard().moveUnit(idUnit, state::Direction::BOT_RIGHT);                  
                break;
        }
    }

}
