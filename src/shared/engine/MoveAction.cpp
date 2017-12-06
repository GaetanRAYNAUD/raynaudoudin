#include "MoveAction.h"
#include "state/State.h"
#include "state/Unit.h"
#include "state/Terrain.h"
#include "state/House.h"

#include <iostream>

namespace engine {

    MoveAction::MoveAction(int idUnit, state::Direction direction, int speed) : idUnit(idUnit), speed(speed), direction(direction) {

    }

    void MoveAction::apply(state::State& state) {
        for(auto& t : state.getBoard().findTerrainAround(state.getBoard().findTerrainOnPosition(state.getBoard().findUnit(idUnit)->getPositionX(), state.getBoard().findUnit(idUnit)->getPositionY())->getId())) {
            if(t->getTypeId() == state::TerrainTypeId::HOUSE) {
                houseTeamId = ((state::House*)t)->getTeamId();
                break;
            }
        }
        state.getBoard().moveUnit(idUnit, direction);
    }

    void MoveAction::undo(state::State& state) {
        if(state.getBoard().findTerrainOnPosition(state.getBoard().findUnit(idUnit)->getPositionX(), state.getBoard().findUnit(idUnit)->getPositionY())->getTypeId() == state::TerrainTypeId::HOUSE) {        
            ((state::House*)state.getBoard().findTerrainOnPosition(state.getBoard().findUnit(idUnit)->getPositionX(), state.getBoard().findUnit(idUnit)->getPositionY()))->setTeamId(houseTeamId);
            state.getBoard().findTeam(state.getBoard().findUnit(idUnit)->getTeam())->removeHouse();
        }
        
        state.getBoard().findUnit(idUnit)->setSpeed(speed);
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
        state.getBoard().findUnit(idUnit)->setSpeed(speed);
    }

}
