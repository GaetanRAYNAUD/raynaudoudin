#include "record.hpp"
#include "../../extern/jsoncpp-1.8.0/json/json.h"

using namespace state;
using namespace engine;
using namespace ai;

namespace record {
    
    void record_test() {
        Engine* engine = new Engine(22, 8);
        HeuristicAI* ai = new HeuristicAI();
        Command* command;
        Json::StyledWriter styledWriter;
        Json::Value jsonCommands;
        std::ofstream fileJson;
        
        fileJson.open("replay.txt");
        
        command = new LoadCommand("res/map.txt");
        engine->addCommand(1, command);
        engine->update(jsonCommands);
        
        while(engine->getState().getWinner() == TeamId::INVALIDTEAM) {
            ai->run(*engine, jsonCommands);
        }
        
        fileJson << styledWriter.write(jsonCommands);        
        fileJson.close();
        
        std::cout << "Commandes enregistrées avec succès !" << std::endl;
        
        delete engine;
        delete ai;
 
    }
}