#include "record.hpp"
#include "json/json.h"

using namespace state;
using namespace engine;
using namespace ai;

namespace record {
    
    void record_test() {
        Engine engine(22, 8);
        HeuristicAI ai;
        Json::StyledWriter styledWriter;
        Json::Value jsonCommands;
        std::ofstream fileJson;
        
        fileJson.open("replay.txt");

        engine.addCommand(1, new LoadCommand("res/map.txt"));
        engine.update();
        
        while(engine.getState().getWinner() == TeamId::INVALIDTEAM) {
            ai.run(engine);
            engine.update();
            engine.addCommand(1, new HandleWinCommand());
            engine.update();
        }
        
        fileJson << styledWriter.write(engine.getCommandHistory());        
        fileJson.close();
        
        std::cout << "Commandes enregistrées avec succès !" << std::endl;
        
 
    }
}