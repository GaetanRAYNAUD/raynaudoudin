#include "RandomAI.h"
#include "engine/EndTurnCommand.h"
#include "engine/HandleWinCommand.h"

namespace ai {

    RandomAI::RandomAI(int randomSeed): randgen(randomSeed) {

    }

    void RandomAI::run(engine::Engine& engine) {
        std::vector<engine::Command*> commands;
        listCommands(engine.getState(), commands);
        commands.push_back(new engine::EndTurnCommand());
        
        if(commands.size() > 0) {
            std::uniform_int_distribution<int> dis(0, commands.size() - 1);
            int rand = dis(randgen);
            engine.addCommand(1, commands.at(rand));
            engine.update();
        } else {
            engine.addCommand(1, new engine::EndTurnCommand());
            engine.update();
        }
            
        engine.addCommand(2, new engine::HandleWinCommand());
        engine.update();
        
        commands.clear();
    }

}
