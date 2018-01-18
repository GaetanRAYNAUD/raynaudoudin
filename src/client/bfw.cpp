#include "bfw.hpp"

using namespace std;
using namespace state;
using namespace ai;
using namespace engine;
using namespace client;

namespace bfw {
    
    void run() {
        int mapWidth = 22;
        int mapHeight = 8;
        int timePause = 100;        
        TeamId playerTeamId = TeamId::TEAM_1;
        TeamId aiTeamId = TeamId::TEAM_2;
        Engine engine(mapWidth, mapHeight);
        HeuristicAI ai = HeuristicAI();
        Client client(engine, playerTeamId);
        sf::Clock clock;
        sf::Time time = clock.getElapsedTime();
        
        thread threadClient = std::thread(&Client::run, std::ref(client));  
        
        while(engine.getState().getWinner() == TeamId::INVALID_TEAM) {
            if(engine.getState().getCurrentTeam() == aiTeamId) {
                if(clock.getElapsedTime().asMilliseconds() - time.asMilliseconds() > timePause) {                
                engine.addCommand(1, ai.run(engine, aiTeamId));
                
                time = clock.getElapsedTime();
                }
            }
            
            engine.addCommand(engine.getCurrentCommands().size(), new HandleWinCommand());            
            engine.update();
            
            usleep(15000);
        }
        
        threadClient.join();
    }
    
}
