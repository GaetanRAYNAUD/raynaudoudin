#include "listen.hpp"

using namespace std;
using namespace server;

namespace listen {

    void listen_Test() {
        try {
            ServicesManager servicesManager;
            Game* game = new Game();
            PlayerService* playerService = new PlayerService(game);
            
            servicesManager.registerService(std::unique_ptr<VersionService>());
            servicesManager.registerService(std::unique_ptr<PlayerService>(playerService));

//            struct MHD_Daemon *d;
//            if (argc != 2) {
//                printf("%s PORT\n", argv[0]);
//                return 1;
//            }
//            d = MHD_start_daemon(// MHD_USE_SELECT_INTERNALLY | MHD_USE_DEBUG | MHD_USE_POLL,
//                    MHD_USE_SELECT_INTERNALLY | MHD_USE_DEBUG,
//                    // MHD_USE_THREAD_PER_CONNECTION | MHD_USE_DEBUG | MHD_USE_POLL,
//                    // MHD_USE_THREAD_PER_CONNECTION | MHD_USE_DEBUG,
//                    atoi(argv[1]),
//                    NULL, NULL, 
//                    &main_handler, (void*) &servicesManager,
//                    MHD_OPTION_NOTIFY_COMPLETED, request_completed, NULL,
//                    MHD_OPTION_END);
//            if (d == NULL)
//                return 1;
//            cout << "Appuyez sur <entrée> pour arrêter le serveur" << endl;
//            (void) getc(stdin);
//            MHD_stop_daemon(d);
        } catch(std::exception& e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        }      
    }
}