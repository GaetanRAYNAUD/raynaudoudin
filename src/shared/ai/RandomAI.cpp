#include "RandomAI.h"

namespace ai {

    RandomAI::RandomAI(int randomSeed): randgen(randomSeed) {

    }

    void RandomAI::run(engine::Engine& engine) {
        std::random_device rd;
        std::vector<engine::Command*> commands = listCommands(engine.getState());
//        commands.at(randgen).execute(engine->getState());
        
        commands.clear();
    }

}
