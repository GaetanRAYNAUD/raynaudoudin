#include "record.hpp"
#include "../../extern/jsoncpp-1.8.0/json/json.h"

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
        engine.update(jsonCommands);
        
        while(engine.getState().getWinner() == TeamId::INVALIDTEAM) {
            ai.run(engine);
            engine.update(jsonCommands);
            engine.addCommand(1, new HandleWinCommand());
            engine.update(jsonCommands);
        }
        
        fileJson << styledWriter.write(jsonCommands);        
        fileJson.close();
        
        std::cout << "Commandes enregistrées avec succès !" << std::endl;
        
 
    }
}